// SPDX-License-Identifier: GPL-2.0-or-later
#include "keymap.h"
#include "audio.h"
#include "compiler_support.h"
#include "keymap_russian.h"
#include "process_audio.h"
#include "process_music.h"

// Each half has six main columns and a seventh column facing inward.
// The red keys appear on the next-to-last line; the six narrow thumb keys are
// last.
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [EN_BASE] = LAYOUT(
        KC_NO,        KC_UNDS, KC_MINS, KC_DOT,  COMMA_SPACE, KC_COLN, KC_AT,       KC_DLR,      KC_GRV,  KC_QUOT, KC_QUES, KC_LPRN, KC_RPRN, HOLD_LOCK,
        KC_TAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,           KC_NO,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
        KC_ESC,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    LCTL(KC_B),      LGUI(KC_SPC), KC_H,   KC_J,    KC_K,    KC_L,    KC_NO,   KC_NO,
        KC_TILD,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,    KC_M,    KC_COMM, KC_NO, UNUSED_E,KC_SLSH,
        LANG_RU,      PIANO_KEY,MO(SYSTEM),KC_NO, APP_NAV_KEY,     KC_BSPC,         KC_ENT,              APP_NAV_KEY,MO(SYMBOLS),MO(NUMBERS),KC_NO,LANG_EN,
                                        OSM(MOD_LSFT), KC_LGUI, KC_LALT,          KC_NO,   KC_RCTL, KC_SPC
    ),
    [RU_BASE] = LAYOUT(
        _______, _______, _______, EN_DOT,  _______, EN_COLN, EN_AT,               EN_DLR,  EN_GRV,  EN_QUOT, EN_QUES, _______, _______, _______,
        _______, RU_SHTI, RU_TSE,  RU_U,    RU_KA,   RU_IE,   _______,             _______, RU_EN,   RU_GHE,  RU_SHA,  RU_SHCH, RU_ZE,   _______,
        _______, RU_EF,   RU_YERU, RU_VE,   RU_A,    RU_PE,   _______,             _______, RU_ER,   RU_O,    RU_EL,   RU_DE,   RU_ZHE,  _______,
        EN_TILD, RU_YA,   RU_CHE,  RU_ES,   RU_EM,   RU_I,                                    RU_TE,   RU_SOFT, RU_BE,   RU_YU,   RU_E,    _______,
        _______, _______, _______, _______, _______,         _______,             _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [APP_NAV] = LAYOUT(
        HELLO_KOTIFY,KC_NO,KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_MPLY, KC_NO,   RCTL(RSFT(KC_TAB)),RCTL(KC_TAB),KC_NO,KC_NO,KC_NO,
        KC_NO,   APP(KC_Q),APP(KC_W),APP(KC_E),APP(KC_R),APP(KC_T),KC_NO,          KC_VOLU, RALT(KC_LEFT),KC_PGDN,KC_PGUP,RALT(KC_RGHT),KC_NO,KC_NO,
        KC_NO,   APP(KC_A),APP(KC_S),APP(KC_D),APP(KC_F),APP(KC_G),KC_NO,          KC_VOLD, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,
        KC_NO,   APP(KC_Z),APP(KC_X),APP(KC_C),APP(KC_V),LGUI(LSFT(KC_5)),                   LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_UP),LGUI(KC_RGHT),KC_NO,KC_NO,
        KC_NO,   _______, _______,KC_NO,   _______,           _______,             _______,          _______, _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [NUMBERS] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   EN_PERC, KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,    EN_ASTR, EN_SLSH,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_0,    KC_4,    KC_5,    KC_6,    KC_PLUS, KC_MINS,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,    KC_EQL,                                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   _______,           _______,             _______,          _______, _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [SYMBOLS] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   EN_PERC, KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   EN_AMPR, EN_LCBR, EN_RCBR, EN_ASTR, KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   EN_HASH, EN_PIPE, EN_LBRC, EN_RBRC, KC_PLUS, KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   EN_CIRC, EN_LT,   EN_GT,   KC_EQL,                                   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   _______,           _______,             _______,          _______, _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [SYSTEM] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   FLASH_KEYMAPP, QK_BOOT,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   RM_TOGG, RM_VALD, RM_VALU, RM_PREV, RM_NEXT, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                    KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   _______,           _______,             _______,          _______, _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [PIANO] = LAYOUT(
        PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,    PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,
        PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,    PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,
        PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,    PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,
        PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,                PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,
        PIANO_NOTE, PIANO_KEY,  PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,             PIANO_NOTE,    PIANO_NOTE,             PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,
                                                    PIANO_NOTE, PIANO_NOTE, PIANO_NOTE,      PIANO_NOTE, PIANO_NOTE, PIANO_NOTE
    ),
};
// clang-format on

static const uint16_t PROGMEM english_symbols[] = {
#define X(name) KC_##name,
    ENGLISH_SYMBOLS(X)
#undef X
};

static uint8_t  english_symbols_held;
static uint8_t  app_nav_keys_held;
static bool     comma_held_with_mods;
static bool     lock_held;
static bool     lock_sent;
static uint16_t lock_timer;

enum { PIANO_HOLD_MS = 200, PIANO_TAP_GAP_MS = 250, PIANO_LOWEST_NOTE = 36 }; // MIDI 36 is C2.
static bool     piano_key_held;
static uint8_t  piano_taps;
static uint32_t piano_key_timer;

// The opening vocal phrase from Adele's "Hello", two octaves up for the buzzer.
static float hello_kotify_song[][2] = SONG(
    ED_NOTE(_AS5), H__NOTE(_C6), M__NOTE(_REST, 56),
    ED_NOTE(_AS5), E__NOTE(_REST), H__NOTE(_AS5)
);

static bool is_russian(void) { return (default_layer_state & (1UL << RU_BASE)) != 0; }

bool is_letter(uint16_t keycode, bool russian) {
    if (keycode >= KC_A && keycode <= KC_Z) {
        return true;
    }
    // These HID punctuation keys type letters in the Russian input source.
    if (russian) {
        switch (keycode) {
        case RU_HA:
        case RU_HARD:
        case RU_ZHE:
        case RU_E:
        case RU_BE:
        case RU_YU:
        case KC_BSLS: // Ё, sent by the R + T combo.
            return true;
        }
    }
    return false;
}

// Russian letters share some HID punctuation keys, so check letters first.
static bool is_symbol(uint16_t keycode, bool russian) {
    return (is_number_key(keycode) || is_punctuation_key(keycode)) && !is_letter(keycode, russian);
}

// Digits and symbols have their own keys, so a lone held Shift must not change them.
static void register_symbol(uint16_t keycode) {
    const uint8_t mods = get_mods();
    if (mods == 0 || (mods & ~MOD_MASK_SHIFT) != 0) {
        register_code16(keycode);
        return;
    }
    del_mods(MOD_MASK_SHIFT);
    register_code16(keycode);
    // Restore Shift for the next keys without sending another report.
    set_mods(mods);
}

typedef struct {
    uint8_t regular;
    uint8_t weak;
    uint8_t oneshot;
} saved_mods_t;

static saved_mods_t save_and_clear_mods(void) {
    const saved_mods_t mods = {get_mods(), get_weak_mods(), get_oneshot_mods()};
    clear_mods();
    clear_weak_mods();
    clear_oneshot_mods();
    send_keyboard_report();
    return mods;
}

static void restore_mods(saved_mods_t mods) {
    set_mods(mods.regular);
    set_weak_mods(mods.weak);
    set_oneshot_mods(mods.oneshot);
    send_keyboard_report();
}

// Time the computer needs to switch input sources before the next symbol.
enum { INPUT_SOURCE_SWITCH_MS = 30 };

static void select_input_source(bool russian) {
    const saved_mods_t mods = save_and_clear_mods();
    tap_code16(russian ? LCTL(LSFT(KC_2)) : LCTL(LSFT(KC_1)));
    wait_ms(INPUT_SOURCE_SWITCH_MS);
    restore_mods(mods);
}

// The computer uses Russian while the keyboard is in Russian and no English symbol is held.
static bool russian_input_expected(void) { return is_russian() && english_symbols_held == 0; }

static void set_language(bool russian) {
    // Keep English underneath Russian so transparent keys retain their bindings.
    default_layer_set((1UL << EN_BASE) | (russian ? (1UL << RU_BASE) : 0));
    // The blue status LED on each half shows Russian.
    STATUS_LED_1(russian);
    STATUS_LED_4(russian);
    select_input_source(russian_input_expected());
}

enum combos {
    CYRILLIC_HA,
    CYRILLIC_HARD_SIGN,
    DOT_SPACE_SHIFT,
    PLAIN_COMMA,
    SEMICOLON,
    DOUBLE_QUOTE,
    CYRILLIC_YO,
    EXCLAMATION,
    BACKSLASH,
    THUMB_SHIFT_ENTER,
    THUMB_COMMAND_ENTER,
    THUMB_WORD_DELETE,
};

const uint16_t PROGMEM ha_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM hard_sign_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM dot_minus_combo[] = {KC_DOT, KC_MINS, COMBO_END};
const uint16_t PROGMEM plain_comma_combo[] = {COMMA_SPACE, KC_DOT, COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {COMMA_SPACE, KC_COLN, COMBO_END};
const uint16_t PROGMEM double_quote_combo[] = {KC_QUOT, KC_QUES, COMBO_END};
const uint16_t PROGMEM yo_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM exclamation_combo[] = {KC_QUES, KC_LPRN, COMBO_END};
const uint16_t PROGMEM backslash_combo[] = {KC_SLSH, UNUSED_E, COMBO_END};
const uint16_t PROGMEM thumb_shift_enter_combo[] = {KC_SPC, KC_ENT, COMBO_END};
const uint16_t PROGMEM thumb_command_enter_combo[] = {KC_RCTL, KC_ENT, COMBO_END};
const uint16_t PROGMEM thumb_word_delete_combo[] = {OSM(MOD_LSFT), KC_BSPC, COMBO_END};

combo_t key_combos[] = {
    [CYRILLIC_HA] = COMBO(ha_combo, RU_HA),
    [CYRILLIC_HARD_SIGN] = COMBO(hard_sign_combo, RU_HARD),
    [DOT_SPACE_SHIFT] = COMBO_ACTION(dot_minus_combo),
    [PLAIN_COMMA] = COMBO(plain_comma_combo, EN_COMM),
    [SEMICOLON] = COMBO(semicolon_combo, EN_SCLN),
    [DOUBLE_QUOTE] = COMBO(double_quote_combo, EN_DQUO),
    [CYRILLIC_YO] = COMBO(yo_combo, KC_BSLS),
    [EXCLAMATION] = COMBO(exclamation_combo, KC_EXLM),
    [BACKSLASH] = COMBO(backslash_combo, EN_BSLS),
    [THUMB_SHIFT_ENTER] = COMBO_ACTION(thumb_shift_enter_combo),
    [THUMB_COMMAND_ENTER] = COMBO_ACTION(thumb_command_enter_combo),
    [THUMB_WORD_DELETE] = COMBO_ACTION(thumb_word_delete_combo),
};

static void tap_punctuation_space(uint8_t punctuation) {
    const saved_mods_t mods = save_and_clear_mods();
    const bool restore_russian = russian_input_expected();
    if (restore_russian) {
        select_input_source(false);
    }
    tap_code(punctuation);
    tap_code(KC_SPC);
    if (restore_russian) {
        select_input_source(true);
    }
    restore_mods(mods);
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) {
        return;
    }
    switch (combo_index) {
    case DOT_SPACE_SHIFT:
        tap_punctuation_space(KC_DOT);
        add_oneshot_mods(MOD_BIT(KC_LSFT));
        break;
    case THUMB_SHIFT_ENTER:
        tap_code16(LSFT(KC_ENT));
        break;
    case THUMB_COMMAND_ENTER:
        tap_code16(LGUI(KC_ENT));
        break;
    case THUMB_WORD_DELETE:
        tap_code16(LALT(KC_BSPC));
        break;
    }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(PIANO)) {
        return false;
    }
    switch (combo_index) {
    case THUMB_SHIFT_ENTER:
    case THUMB_COMMAND_ENTER:
    case THUMB_WORD_DELETE:
        return true;
    }
    const uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    if (layer != EN_BASE && layer != RU_BASE) {
        return false;
    }
    switch (combo_index) {
    case CYRILLIC_HA:
    case CYRILLIC_HARD_SIGN:
    case CYRILLIC_YO:
        return is_russian();
    default:
        return true;
    }
}

static void stop_piano(void) {
    audio_stop_all();
    layer_off(PIANO);
}

static void process_piano_key(bool pressed) {
    if (pressed) {
        if (layer_state_is(PIANO)) {
            stop_piano();
        } else {
            if (timer_elapsed32(piano_key_timer) >= PIANO_TAP_GAP_MS) {
                piano_taps = 0;
            }
            piano_key_held  = true;
            piano_key_timer = timer_read32();
        }
    } else if (piano_key_held) {
        piano_key_held = false;
        if (layer_state_is(PIANO)) {
            stop_piano();
        } else if (timer_elapsed32(piano_key_timer) >= PIANO_HOLD_MS) {
            piano_taps = 0;
        } else if (++piano_taps == 3) {
            piano_taps = 0;
            layer_on(PIANO);
        } else {
            piano_key_timer = timer_read32();
        }
    }
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == PIANO_KEY) {
        process_piano_key(record->event.pressed);
        return false;
    }
    if (record->event.pressed) {
        piano_taps = 0;
        if (piano_key_held && !layer_state_is(PIANO)) {
            // QMK looks up this key again after the layer changes.
            layer_on(PIANO);
        }
    }
    return true;
}

static void hello_kotify(void) {
    PLAY_SONG(hello_kotify_song);
    const saved_mods_t mods = save_and_clear_mods();
    select_input_source(false);
    tap_code16(APP(KC_G));
    // The keyboard cannot see which window is focused, so give the app time to come forward.
    wait_ms(300);
    tap_code(KC_ESC);
    tap_code(KC_ESC);
    tap_code16(LGUI(KC_F));
    wait_ms(50);
    SEND_STRING("kotify ser");
    wait_ms(300);
    tap_code(KC_ENT);
    wait_ms(100);
    select_input_source(true);
    wait_ms(50);
    tap_code16(LSFT(KC_G));
    tap_code(KC_H);
    tap_code(KC_B);
    tap_code(KC_D);
    tap_code(KC_T);
    tap_code(KC_N);
    wait_ms(50);
    select_input_source(russian_input_expected());
    restore_mods(mods);
}

// Opens Keymapp, picks dist/moonlander-reva.bin in its file dialog, and enters the bootloader.
static void flash_keymapp(void) {
    save_and_clear_mods();
    tap_code16(APP(KC_Q));
    wait_ms(1000);
    // Open the flash dialog.
    tap_code(KC_TAB);
    tap_code(KC_SPC);
    wait_ms(500);
    // Open the firmware file dialog.
    for (uint8_t i = 0; i < 5; ++i) {
        tap_code(KC_TAB);
    }
    tap_code(KC_SPC);
    wait_ms(1000);
    // The firmware is the second file in the dialog.
    tap_code(KC_DOWN);
    tap_code(KC_DOWN);
    tap_code(KC_ENT);
    wait_ms(500);
    reset_keyboard();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // A one-shot Shift only capitalizes the next letter; it survives a language switch.
    if (record->event.pressed && (get_oneshot_mods() & MOD_MASK_SHIFT) && keycode != LANG_EN && keycode != LANG_RU &&
        !is_letter(keycode, is_russian())) {
        del_oneshot_mods(MOD_MASK_SHIFT);
    }

    if (keycode == COMMA_SPACE) {
        if (record->event.pressed) {
            comma_held_with_mods = ((get_mods() | get_weak_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0;
            if (!comma_held_with_mods) {
                tap_punctuation_space(KC_COMM);
            }
        }
        if (!comma_held_with_mods) {
            return false;
        }
        comma_held_with_mods = record->event.pressed;
        keycode = EN_COMM;
    }

    if (is_english_symbol(keycode)) {
        const uint16_t output = pgm_read_word(&english_symbols[keycode - EN_DOT]);
        if (record->event.pressed) {
            if (russian_input_expected()) {
                select_input_source(false);
            }
            ++english_symbols_held;
            register_symbol(output);
        } else {
            unregister_code16(output);
            if (english_symbols_held > 0) {
                --english_symbols_held;
                if (russian_input_expected()) {
                    select_input_source(true);
                }
            }
        }
        return false;
    }

    if (is_symbol(keycode, is_russian())) {
        if (record->event.pressed) {
            register_symbol(keycode);
        } else {
            unregister_code16(keycode);
        }
        return false;
    }

    switch (keycode) {
    case PIANO_NOTE: {
        const uint8_t note = PIANO_LOWEST_NOTE + music_map[record->event.key.row][record->event.key.col];
        if (record->event.pressed) {
            if (audio_is_playing_melody()) {
                audio_stop_all();
            }
            process_audio_noteon(note);
        } else if (layer_state_is(PIANO)) {
            process_audio_noteoff(note);
        }
        return false;
    }
    case LANG_EN:
    case LANG_RU:
        if (record->event.pressed) {
            set_language(keycode == LANG_RU);
        }
        return false;
    case APP_NAV_KEY:
        // Keep the layer active until both layer keys are released.
        if (record->event.pressed) {
            if (++app_nav_keys_held == 1) {
                layer_on(APP_NAV);
            }
        } else if (app_nav_keys_held > 0 && --app_nav_keys_held == 0) {
            layer_off(APP_NAV);
        }
        return false;
    case HELLO_KOTIFY:
        if (record->event.pressed) {
            hello_kotify();
        }
        return false;
    case FLASH_KEYMAPP:
        if (record->event.pressed) {
            flash_keymapp();
        }
        return false;
    case HOLD_LOCK:
        lock_held = record->event.pressed;
        if (lock_held) {
            lock_timer = timer_read();
            lock_sent = false;
        }
        return false;
    case UNUSED_E:
        // This key only takes part in a combo.
        return false;
    default:
        return true;
    }
}

void matrix_scan_user(void) {
    if (piano_key_held && !layer_state_is(PIANO) && timer_elapsed32(piano_key_timer) >= PIANO_HOLD_MS) {
        piano_taps = 0;
        layer_on(PIANO);
    }
    if (lock_held && !lock_sent && timer_elapsed(lock_timer) >= 1000) {
        const saved_mods_t mods = save_and_clear_mods();
        tap_code16(LGUI(LCTL(KC_Q)));
        restore_mods(mods);
        lock_sent = true;
    }
}
