// SPDX-License-Identifier: GPL-2.0-or-later
#include "rgb.h"
#include "keymap.h"
#include "keymap_russian.h"

STATIC_ASSERT(RGB_MATRIX_EFFECT_MAX == 5, "Only four RGB modes should be enabled");

// clang-format off
static const rgb_t layer_colors[] = {
    [EN_BASE]    = {255, 255, 255},
    [RU_BASE]    = {0, 0, 255},
    [APPS]       = {128, 0, 255},
    [NAV]        = {0, 255, 255},
    [NUMBERS]    = {0, 255, 0},
    [SYMBOLS_EN] = {255, 128, 0},
    [SYMBOLS_RU] = {255, 128, 0},
    [SYSTEM]     = {255, 0, 0},
};
// clang-format on

enum finger { PINKY, RING, MIDDLE, INDEX };

static const rgb_t finger_colors[] = {
    [PINKY] = {255, 0, 128},
    [RING] = {255, 192, 0},
    [MIDDLE] = {0, 255, 0},
    [INDEX] = {0, 192, 255},
};

static const uint8_t finger_columns[2][MATRIX_COLS] = {
    {PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX},
    {INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY},
};

enum key_role { UNUSED, LETTER, NUMBER, SYMBOL, MODIFIER, EDITING, NAVIGATION, LAYER, SHORTCUT, MEDIA, CONTROL };

// clang-format off
static const rgb_t role_colors[] = {
    [UNUSED]     = {0, 0, 0},
    [LETTER]     = {255, 255, 255},
    [NUMBER]     = {0, 255, 0},
    [SYMBOL]     = {255, 192, 0},
    [MODIFIER]   = {0, 96, 255},
    [EDITING]    = {255, 128, 0},
    [NAVIGATION] = {0, 255, 255},
    [LAYER]      = {255, 64, 0},
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

static rgb_t layer_color(void) { return layer_colors[get_highest_layer(layer_state | default_layer_state)]; }

// Built-in effects keep their brightness animation and use the layer's RGB color.
rgb_t rgb_matrix_hsv_to_rgb(hsv_t hsv) { return scale_color(layer_color(), hsv.v); }

static bool is_thumb_row(uint8_t row) { return row == 5 || row == 11; }

static enum key_role key_role(uint16_t keycode, uint8_t source_layer) {
    if (keycode == KC_NO || keycode == KC_TRNS || keycode == UNUSED_BE || keycode == UNUSED_E) {
        return UNUSED;
    }
    if (IS_QK_MOMENTARY(keycode) || keycode == LANG_SWITCH) {
        return LAYER;
    }
    if (keycode >= EN_DOT && keycode <= EN_BSLS) {
        return SYMBOL;
    }
    if (keycode == HELLO_KOTIFY) {
        return SHORTCUT;
    }
    if (keycode == HOLD_LOCK || keycode == QK_BOOTLOADER || IS_RGB_MATRIX_KEYCODE(keycode)) {
        return CONTROL;
    }

    const uint16_t basic = IS_QK_MODS(keycode) ? QK_MODS_GET_BASIC_KEYCODE(keycode) : keycode;
    if ((basic >= KC_RIGHT && basic <= KC_UP) || (basic >= KC_INSERT && basic <= KC_PAGE_DOWN && basic != KC_DELETE)) {
        return NAVIGATION;
    }
    if (IS_QK_MODS(keycode)) {
        const uint8_t mods = QK_MODS_GET_MODS(keycode);
        if ((mods == MOD_LSFT || mods == (0x10 | MOD_LSFT)) &&
            ((basic >= KC_1 && basic <= KC_0) || (basic >= KC_MINUS && basic <= KC_SLASH))) {
            return SYMBOL;
        }
        return SHORTCUT;
    }
    if (IS_MODIFIER_KEYCODE(keycode)) {
        return MODIFIER;
    }
    // These HID punctuation keys are letters when supplied by the Russian layer.
    if (source_layer == RU_BASE) {
        switch (keycode) {
        case RU_YO:
        case RU_HA:
        case RU_HARD:
        case RU_ZHE:
        case RU_E:
        case RU_BE:
        case RU_YU:
            return LETTER;
        }
    }
    if (keycode >= KC_A && keycode <= KC_Z) {
        return LETTER;
    }
    if (keycode >= KC_1 && keycode <= KC_0) {
        return NUMBER;
    }
    if (keycode >= KC_MINUS && keycode <= KC_SLASH) {
        return SYMBOL;
    }
    if (IS_CONSUMER_KEYCODE(keycode)) {
        return MEDIA;
    }
    return EDITING;
}

void render_finger_zones(uint8_t led_min, uint8_t led_max) {
    const uint8_t brightness = rgb_matrix_get_flags() == LED_FLAG_NONE ? 0 : rgb_matrix_get_val();
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) {
                continue;
            }
            const rgb_t color = scale_color(finger_colors[finger_columns[row >= MATRIX_ROWS / 2][col]], brightness);
            rgb_matrix_set_color(led, color.r, color.g, color.b);
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    const uint8_t brightness = rgb_matrix_get_val();
    // Keep indicators visible even when the main backlight is off or at zero.
    const rgb_t thumb_color = scale_color(layer_color(), MAX(brightness, 16));
    const bool  roles_enabled =
        rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR && rgb_matrix_get_flags() != LED_FLAG_NONE;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            const uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) {
                continue;
            }
            if (is_thumb_row(row)) {
                rgb_matrix_set_color(led, thumb_color.r, thumb_color.g, thumb_color.b);
            } else if (roles_enabled) {
                const keypos_t key = {.row = row, .col = col};
                const uint8_t  source_layer = layer_switch_get_layer(key);
                const uint16_t keycode = keymap_key_to_keycode(source_layer, key);
                const rgb_t    color = scale_color(role_colors[key_role(keycode, source_layer)], brightness);
                rgb_matrix_set_color(led, color.r, color.g, color.b);
            }
        }
    }
    return false;
}

void keyboard_post_init_user(void) {
    // The RGB thumb keys replace Moonlander's separate layer status LEDs.
    keyboard_config.led_level = false;
    STATUS_LED_1(false);
    STATUS_LED_2(false);
    STATUS_LED_3(false);
    STATUS_LED_4(false);
    STATUS_LED_5(false);
    STATUS_LED_6(false);

    // An old animation index may no longer exist after removing other effects.
    if (rgb_matrix_get_mode() == RGB_MATRIX_NONE || rgb_matrix_get_mode() >= RGB_MATRIX_EFFECT_MAX) {
        rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
    }
    rgb_matrix_set_speed_noeeprom(RGB_MATRIX_DEFAULT_SPD);
    rgb_matrix_set_flags_noeeprom(keyboard_config.rgb_matrix_enable ? LED_FLAG_ALL : LED_FLAG_NONE);
}
