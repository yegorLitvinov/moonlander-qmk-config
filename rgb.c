// SPDX-License-Identifier: GPL-2.0-or-later
#include "rgb.h"
#include "eeconfig.h"
#include "keymap.h"
#include <lib/lib8tion/lib8tion.h>
#include <string.h>

STATIC_ASSERT(RGB_MATRIX_EFFECT_MAX == 5, "Only four RGB modes should be enabled");
STATIC_ASSERT(RGB_MATRIX_CUSTOM_HEATMAP == 2 && RGB_MATRIX_CUSTOM_QUICK_FADE == 3 && RGB_MATRIX_CUSTOM_FINGER_ZONES == 4,
              "Keep the saved RGB mode indices");

enum { HEATMAP_STEP_MS = 25, HEATMAP_PRESS_HEAT = 32, FADE_BASE_MS = 300, FADE_STEP_MS = 175, MAX_DURATION_LEVEL = 4 };

static const uint32_t effect_settings_version = 0x01000000;
static const uint8_t  fade_radii[] = {0, 24, 32, 48};

static uint8_t heatmap_duration = 1;
static uint8_t fade_duration = 2;
static uint8_t fade_spread = 1;

static uint8_t  tracked_mode;
static uint8_t  heatmap[RGB_MATRIX_LED_COUNT];
static uint32_t heatmap_cooled_at;
static uint32_t fade_pressed_at[RGB_MATRIX_LED_COUNT];
static bool     fade_active[RGB_MATRIX_LED_COUNT];
static uint8_t  fade_brightness[RGB_MATRIX_LED_COUNT];

// clang-format off
static const rgb_t layer_colors[] = {
    [EN_BASE]    = {255, 255, 255},
    [RU_BASE]    = {0, 0, 255},
    [APP_NAV]    = {128, 0, 255},
    [NUMBERS]    = {0, 255, 0},
    [SYMBOLS]    = {255, 128, 0},
    [SYSTEM]     = {255, 0, 0},
    [PIANO]      = {255, 224, 0},
};
// clang-format on

STATIC_ASSERT(ARRAY_SIZE(layer_colors) == LAYER_COUNT, "Every layer needs a color");

enum finger { PINKY, RING, MIDDLE, INDEX, THUMB };

static const rgb_t finger_colors[] = {
    [PINKY] = {255, 0, 128},
    [RING] = {255, 192, 0},
    [MIDDLE] = {0, 255, 0},
    [INDEX] = {0, 192, 255},
    [THUMB] = {128, 0, 255},
};

static const uint8_t finger_columns[2][MATRIX_COLS] = {
    {PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX},
    {INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY},
};

enum key_role { LETTER, NUMBER, SYMBOL, MODIFIER, EDITING, NAVIGATION, SHORTCUT, MEDIA, CONTROL };

// clang-format off
static const rgb_t role_colors[] = {
    [LETTER]     = {255, 255, 255},
    [NUMBER]     = {0, 255, 0},
    [SYMBOL]     = {255, 192, 0},
    [MODIFIER]   = {0, 96, 255},
    [EDITING]    = {255, 128, 0},
    [NAVIGATION] = {0, 255, 255},
    [SHORTCUT]   = {255, 0, 255},
    [MEDIA]      = {128, 0, 255},
    [CONTROL]    = {255, 0, 0},
};
// clang-format on

static rgb_t scale_color(rgb_t color, uint8_t brightness) {
    return (rgb_t){
        .r = (uint16_t)color.r * brightness / UINT8_MAX,
        .g = (uint16_t)color.g * brightness / UINT8_MAX,
        .b = (uint16_t)color.b * brightness / UINT8_MAX,
    };
}

static uint8_t active_layer(void) { return get_highest_layer(layer_state | default_layer_state); }

static void load_effect_settings(void) {
    const uint32_t settings = eeconfig_read_user();
    if ((settings & 0xFF000000) == effect_settings_version) {
        heatmap_duration = MIN((uint8_t)(settings >> 16), MAX_DURATION_LEVEL);
        fade_duration = MIN((uint8_t)(settings >> 8), MAX_DURATION_LEVEL);
        fade_spread = MIN((uint8_t)settings, ARRAY_SIZE(fade_radii) - 1);
    }
}

void adjust_rgb_effect(uint16_t keycode) {
    const bool spread = keycode == FX_SPREAD_DOWN || keycode == FX_SPREAD_UP;
    const bool increase = keycode == FX_DURATION_UP || keycode == FX_SPREAD_UP;
    const uint8_t mode = rgb_matrix_get_mode();
    uint8_t *setting;
    uint8_t max_level = MAX_DURATION_LEVEL;

    if (mode == RGB_MATRIX_CUSTOM_QUICK_FADE) {
        setting = &fade_duration;
        if (spread) {
            setting = &fade_spread;
            max_level = ARRAY_SIZE(fade_radii) - 1;
        }
    } else if (mode == RGB_MATRIX_CUSTOM_HEATMAP && !spread) {
        setting = &heatmap_duration;
    } else {
        return;
    }

    const int level = *setting + (increase ? 1 : -1);
    if (level >= 0 && level <= max_level) {
        *setting = level;
        eeconfig_update_user(effect_settings_version | ((uint32_t)heatmap_duration << 16) | ((uint32_t)fade_duration << 8) | fade_spread);
    }
}

void rgb_effects_scan(void) {
    const uint8_t mode = rgb_matrix_is_enabled() && rgb_matrix_get_flags() != LED_FLAG_NONE ? rgb_matrix_get_mode() : RGB_MATRIX_NONE;
    if (mode == tracked_mode) {
        return;
    }
    tracked_mode = mode;
    if (mode == RGB_MATRIX_CUSTOM_HEATMAP) {
        memset(heatmap, 0, sizeof(heatmap));
        heatmap_cooled_at = timer_read32();
    } else if (mode == RGB_MATRIX_CUSTOM_QUICK_FADE) {
        memset(fade_active, 0, sizeof(fade_active));
        memset(fade_brightness, 0, sizeof(fade_brightness));
    }
}

static void cool_heatmap(uint32_t now) {
    const uint16_t interval = HEATMAP_STEP_MS * (heatmap_duration + 1);
    const uint32_t steps = TIMER_DIFF_32(now, heatmap_cooled_at) / interval;
    if (steps == 0) {
        return;
    }

    heatmap_cooled_at += steps * interval;
    const uint8_t cooling = MIN(steps, UINT8_MAX);
    for (uint8_t led = 0; led < RGB_MATRIX_LED_COUNT; ++led) {
        heatmap[led] = qsub8(heatmap[led], cooling);
    }
}

void rgb_effect_keypress(uint8_t row, uint8_t col) {
    const uint8_t led = g_led_config.matrix_co[row][col];
    if (led == NO_LED) {
        return;
    }
    if (tracked_mode == RGB_MATRIX_CUSTOM_HEATMAP) {
        cool_heatmap(timer_read32());
        heatmap[led] = qadd8(heatmap[led], HEATMAP_PRESS_HEAT);
    } else if (tracked_mode == RGB_MATRIX_CUSTOM_QUICK_FADE) {
        fade_pressed_at[led] = timer_read32();
        fade_active[led] = true;
    }
}

void render_heatmap(uint8_t led_min, uint8_t led_max, uint8_t flags) {
    if (led_min == 0) {
        cool_heatmap(timer_read32());
    }

    const uint8_t brightness = rgb_matrix_get_val();
    const uint8_t saturation = rgb_matrix_get_sat();
    for (uint8_t led = led_min; led < led_max; ++led) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[led], flags)) {
            continue;
        }
        const uint8_t heat = heatmap[led];
        const hsv_t   hsv = {170 - qsub8(heat, 85), saturation, scale8(MIN(heat * 3, UINT8_MAX), brightness)};
        const rgb_t   color = hsv_to_rgb(hsv);
        rgb_matrix_set_color(led, color.r, color.g, color.b);
    }
}

static uint8_t fade_brightness_at_distance(uint8_t source, uint8_t target, uint8_t radius, uint8_t brightness) {
    const int32_t dx = g_led_config.point[source].x - g_led_config.point[target].x;
    const int32_t dy = g_led_config.point[source].y - g_led_config.point[target].y;
    const int32_t distance_squared = dx * dx + dy * dy;
    if (distance_squared >= radius * radius) {
        return 0;
    }
    // A quadratic falloff keeps the pressed key brightest and dims distant keys faster.
    const uint16_t remaining = radius - sqrt16(distance_squared);
    return (uint32_t)brightness * remaining * remaining / (radius * radius);
}

static void update_fade_brightness(void) {
    const uint32_t now = timer_read32();
    const uint16_t duration = FADE_BASE_MS + FADE_STEP_MS * fade_duration;
    const uint8_t  radius = fade_radii[fade_spread];
    memset(fade_brightness, 0, sizeof(fade_brightness));

    for (uint8_t source = 0; source < RGB_MATRIX_LED_COUNT; ++source) {
        if (!fade_active[source]) {
            continue;
        }
        const uint32_t age = TIMER_DIFF_32(now, fade_pressed_at[source]);
        if (age >= duration) {
            fade_active[source] = false;
            continue;
        }

        const uint8_t brightness = (duration - age) * UINT8_MAX / duration;
        if (radius == 0) {
            fade_brightness[source] = brightness;
            continue;
        }
        for (uint8_t led = 0; led < RGB_MATRIX_LED_COUNT; ++led) {
            const uint8_t nearby = fade_brightness_at_distance(source, led, radius, brightness);
            fade_brightness[led] = MAX(fade_brightness[led], nearby);
        }
    }
}

void render_quick_fade(uint8_t led_min, uint8_t led_max, uint8_t flags) {
    if (led_min == 0) {
        update_fade_brightness();
    }

    const rgb_t   active_color = layer_colors[active_layer()];
    const uint8_t brightness = rgb_matrix_get_val();
    for (uint8_t led = led_min; led < led_max; ++led) {
        if (HAS_ANY_FLAGS(g_led_config.flags[led], flags)) {
            const rgb_t color = scale_color(active_color, scale8(fade_brightness[led], brightness));
            rgb_matrix_set_color(led, color.r, color.g, color.b);
        }
    }
}

static bool is_thumb_row(uint8_t row) { return row == 5 || row == 11; }

static bool key_has_action(uint16_t keycode) { return keycode != KC_NO && keycode != KC_TRNS && keycode != UNUSED_E; }

static enum key_role key_role(uint16_t keycode, uint8_t source_layer) {
    if (is_english_symbol(keycode) || keycode == COMMA_SPACE) {
        return SYMBOL;
    }
    if (keycode == HELLO_KOTIFY) {
        return SHORTCUT;
    }
    if (keycode == HOLD_LOCK || keycode == FLASH_KEYMAPP || keycode == QK_BOOTLOADER || IS_RGB_MATRIX_KEYCODE(keycode) ||
        (keycode >= FX_DURATION_DOWN && keycode <= FX_SPREAD_UP)) {
        return CONTROL;
    }

    const uint16_t basic = IS_QK_MODS(keycode) ? QK_MODS_GET_BASIC_KEYCODE(keycode) : keycode;
    if ((basic >= KC_RIGHT && basic <= KC_UP) || (basic >= KC_INSERT && basic <= KC_PAGE_DOWN && basic != KC_DELETE)) {
        return NAVIGATION;
    }
    if (IS_QK_MODS(keycode)) {
        const uint8_t mods = QK_MODS_GET_MODS(keycode);
        if ((mods == MOD_LSFT || mods == (0x10 | MOD_LSFT)) &&
            (is_number_key(basic) || is_punctuation_key(basic))) {
            return SYMBOL;
        }
        return SHORTCUT;
    }
    if (IS_MODIFIER_KEYCODE(keycode) || IS_QK_ONE_SHOT_MOD(keycode)) {
        return MODIFIER;
    }
    if (is_letter(keycode, source_layer == RU_BASE)) {
        return LETTER;
    }
    if (is_number_key(keycode)) {
        return NUMBER;
    }
    if (is_punctuation_key(keycode)) {
        return SYMBOL;
    }
    if (IS_CONSUMER_KEYCODE(keycode) || keycode == PIANO_NOTE) {
        return MEDIA;
    }
    return EDITING;
}

static rgb_t key_color(uint16_t keycode, uint8_t source_layer) {
    switch (keycode) {
    case LANG_EN:
        return layer_colors[EN_BASE];
    case LANG_RU:
        return layer_colors[RU_BASE];
    case APP_NAV_KEY:
        return layer_colors[APP_NAV];
    case PIANO_KEY:
        return layer_colors[PIANO];
    default:
        if (IS_QK_MOMENTARY(keycode)) {
            const uint8_t target = QK_MOMENTARY_GET_LAYER(keycode);
            if (target < LAYER_COUNT) {
                return layer_colors[target];
            }
        }
        return role_colors[key_role(keycode, source_layer)];
    }
}

static enum finger key_finger(keypos_t key) {
    if (keymap_key_to_keycode(EN_BASE, key) == APP_NAV_KEY) {
        return THUMB;
    }
    if ((key.row == 0 && key.col == 0) || (key.row == MATRIX_ROWS / 2 && key.col == MATRIX_COLS - 1)) {
        return RING;
    }
    return finger_columns[key.row >= MATRIX_ROWS / 2][key.col];
}

void render_finger_zones(uint8_t led_min, uint8_t led_max) {
    const uint8_t brightness = rgb_matrix_get_flags() == LED_FLAG_NONE ? 0 : rgb_matrix_get_val();
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) {
                continue;
            }
            const keypos_t key = {.row = row, .col = col};
            const rgb_t color = scale_color(finger_colors[key_finger(key)], brightness);
            rgb_matrix_set_color(led, color.r, color.g, color.b);
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
        return false;
    }

    const uint8_t brightness = rgb_matrix_get_val();
    const uint8_t layer = active_layer();
    // Keep indicators visible at low brightness while RGB is on.
    const rgb_t indicator_color = scale_color(layer_colors[layer], MAX(brightness, 16));
    const bool  roles_enabled   = rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR;
    const bool  show_layer_color = layer > RU_BASE;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) {
                continue;
            }
            if (is_thumb_row(row)) {
                rgb_matrix_set_color(led, indicator_color.r, indicator_color.g, indicator_color.b);
            } else if (roles_enabled) {
                const keypos_t key = {.row = row, .col = col};
                const uint8_t  source_layer = show_layer_color ? layer : layer_switch_get_layer(key);
                const uint16_t keycode = keymap_key_to_keycode(source_layer, key);
                rgb_t color = {0};
                if (key_has_action(keycode)) {
                    color = scale_color(show_layer_color ? layer_colors[layer] : key_color(keycode, source_layer), brightness);
                }
                rgb_matrix_set_color(led, color.r, color.g, color.b);
            }
        }
    }
    return false;
}

void keyboard_post_init_user(void) {
    // An old animation index may no longer exist after removing other effects.
    if (rgb_matrix_get_mode() == RGB_MATRIX_NONE || rgb_matrix_get_mode() >= RGB_MATRIX_EFFECT_MAX) {
        rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
    }
    load_effect_settings();
    rgb_matrix_set_flags_noeeprom(keyboard_config.rgb_matrix_enable ? LED_FLAG_ALL : LED_FLAG_NONE);
}
