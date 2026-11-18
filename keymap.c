// SPDX-License-Identifier: GPL-2.0-or-later
#include "keymap.h"
#include "audio.h"
#include "compiler_support.h"
#include "keymap_russian.h"
#include "process_audio.h"
#include "process_music.h"

// Each side keeps the K03's six main columns. The seventh column faces inward.
// The red keys appear on the next-to-last line; the six narrow thumb keys are
// last.
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [EN_BASE] = LAYOUT(
        KC_NO,        KC_UNDS, KC_MINS, KC_DOT,  KC_COMM, KC_COLN, KC_NO,           KC_NO,       KC_GRV,  KC_QUOT, KC_QUES, KC_LPRN, KC_RPRN, HOLD_LOCK,
        KC_TAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO,           KC_NO,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
        KC_ESC,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    LCTL(KC_B),      KC_NO,       KC_H,    KC_J,    KC_K,    KC_L,    KC_NO,   KC_NO,
        KC_TILD,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,    KC_M,    UNUSED_BE,KC_NO, UNUSED_E,KC_SLSH,
        KC_NO,        PIANO_KEY,MO(SYSTEM),KC_NO, KC_NO,           MO(APPS),        MO(NAV),             LANG_SWITCH,MO(SYMBOLS_EN),MO(NUMBERS),KC_NO,KC_DLR,
                                              KC_LSFT, KC_LGUI, KC_BSPC,          KC_ENT,  KC_RCTL, KC_SPC
    ),
    [RU_BASE] = LAYOUT(
        _______, _______, _______, EN_DOT,  EN_COMM, EN_COLN, _______,             _______, EN_GRV,  EN_QUOT, EN_QUES, _______, _______, _______,
        _______, RU_SHTI, RU_TSE,  RU_U,    RU_KA,   RU_IE,   _______,             _______, RU_EN,   RU_GHE,  RU_SHA,  RU_SHCH, RU_ZE,   _______,
        _______, RU_EF,   RU_YERU, RU_VE,   RU_A,    RU_PE,   _______,             _______, RU_ER,   RU_O,    RU_EL,   RU_DE,   RU_ZHE,  _______,
        EN_TILD, RU_YA,   RU_CHE,  RU_ES,   RU_EM,   RU_I,                                    RU_TE,   RU_SOFT, RU_BE,   RU_YU,   RU_E,    _______,
        _______, _______, _______, _______, _______,         _______,             _______,          _______, _______, _______, _______, EN_DLR,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [APPS] = LAYOUT(
        HELLO_KOTIFY,KC_NO,KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   APP(KC_Q),APP(KC_W),APP(KC_E),APP(KC_R),APP(KC_T),KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   APP(KC_A),APP(KC_S),APP(KC_D),APP(KC_F),APP(KC_G),KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   APP(KC_Z),APP(KC_X),APP(KC_C),APP(KC_V),LGUI(LSFT(KC_5)),                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   KC_NO,             _______,             _______,          KC_NO,   _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [NAV] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   RCTL(RSFT(KC_TAB)),RCTL(KC_TAB),KC_NO,KC_NO,KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   RALT(KC_LEFT),KC_PGDN,KC_PGUP,RALT(KC_RGHT),KC_NO,KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                    LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_UP),LGUI(KC_RGHT),KC_NO,KC_NO,
        KC_NO,   _______, _______,KC_NO,   KC_NO,             _______,             _______,          KC_NO,   _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [NUMBERS] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   EN_PLUS, EN_MINS,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,    EN_ASTR, EN_SLSH,             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_0,    KC_4,    KC_5,    KC_6,    EN_EQL,  KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,    EN_PERC,                                  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   KC_NO,             _______,             _______,          KC_NO,   _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [SYMBOLS_EN] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_LCBR, KC_RCBR, KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_AT,   KC_HASH, KC_LBRC, KC_RBRC, KC_AMPR, KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_CIRC, KC_PIPE, KC_LT,   KC_GT,   KC_NO,                                    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   KC_NO,             _______,             _______,          KC_NO,   _______,_______,KC_NO,   KC_NO,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [SYMBOLS_RU] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, EN_LCBR, EN_RCBR, _______, _______,             _______, _______, _______, _______, _______, _______, _______,
        _______, EN_AT,   EN_HASH, EN_LBRC, EN_RBRC, EN_AMPR, _______,             _______, _______, _______, _______, _______, _______, _______,
        _______, EN_CIRC, EN_PIPE, EN_LT,   EN_GT,   _______,                                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,         _______,             _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,             _______, _______, _______
    ),
    [SYSTEM] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   RM_TOGG, RM_VALD, RM_VALU, RM_PREV, RM_NEXT, KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_MPLY, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                    KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_NO,
        KC_NO,   _______, _______,KC_NO,   KC_NO,             _______,             _______,          KC_NO,   _______,_______,KC_NO,   KC_NO,
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
    KC_DOT,  KC_COMM, KC_COLN, KC_GRV,  KC_QUOT, KC_QUES, KC_TILD, KC_LT,   KC_GT,   KC_EQL,  KC_LCBR, KC_RCBR, KC_PLUS,
    KC_ASTR, KC_PERC, KC_LBRC, KC_RBRC, KC_AT,   KC_DLR,  KC_HASH, KC_CIRC, KC_PIPE, KC_AMPR, KC_SCLN, KC_DQUO, KC_MINS, KC_SLSH, KC_BSLS,
};

STATIC_ASSERT(ARRAY_SIZE(english_symbols) == EN_BSLS - EN_DOT + 1, "English symbol outputs must match their keycodes");

static uint8_t  english_symbols_held;
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

// Piano pitches under A, D, G, D, A, and Z.
static float piano_start_song[][2] = SONG(Q__NOTE(_G4), Q__NOTE(_A4), Q__NOTE(_B4), Q__NOTE(_A4), Q__NOTE(_G4), E__NOTE(_REST), Q__NOTE(_G3));

static bool is_russian(void) { return (default_layer_state & (1UL << RU_BASE)) != 0; }

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

static void select_input_source(bool russian) {
    const saved_mods_t mods = save_and_clear_mods();
    tap_code16(russian ? LCTL(LSFT(KC_2)) : LCTL(LSFT(KC_1)));
    // Match the K03's language-switch delay before sending the next symbol.
    wait_ms(TAP_CODE_DELAY);
    restore_mods(mods);
}

static void set_language(bool russian) {
    // Keep English underneath Russian so transparent keys retain their bindings.
    default_layer_set((1UL << EN_BASE) | (russian ? (1UL << RU_BASE) : 0));
    layer_state_set(layer_state);
    select_input_source(russian && english_symbols_held == 0);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Keep the English Symbols layer active beneath its Russian overlay.
    if (is_russian() && (state & (1UL << SYMBOLS_EN))) {
        state |= 1UL << SYMBOLS_RU;
    } else {
        state &= ~(1UL << SYMBOLS_RU);
    }
    return state;
}

enum combos {
    CYRILLIC_HA,
    CYRILLIC_HARD_SIGN,
    SEMICOLON,
    DOUBLE_QUOTE,
    CYRILLIC_YO,
    EXCLAMATION,
    BACKSLASH,
    THUMB_SHIFT_ENTER,
    THUMB_COMMAND_ENTER,
    THUMB_ALT,
    THUMB_COMMAND_BACKSPACE,
};

const uint16_t PROGMEM ha_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM hard_sign_combo[] = {KC_M, UNUSED_BE, COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {KC_DOT, KC_COMM, COMBO_END};
const uint16_t PROGMEM double_quote_combo[] = {KC_GRV, KC_QUOT, COMBO_END};
const uint16_t PROGMEM yo_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM exclamation_combo[] = {KC_QUOT, KC_QUES, COMBO_END};
const uint16_t PROGMEM backslash_combo[] = {KC_SLSH, UNUSED_E, COMBO_END};
const uint16_t PROGMEM thumb_shift_enter_combo[] = {KC_RCTL, KC_ENT, COMBO_END};
const uint16_t PROGMEM thumb_command_enter_combo[] = {MO(NAV), KC_RCTL, KC_ENT, COMBO_END};
const uint16_t PROGMEM thumb_alt_combo[] = {MO(NAV), KC_SPC, COMBO_END};
const uint16_t PROGMEM thumb_command_backspace_combo[] = {MO(APPS), KC_LGUI, KC_BSPC, COMBO_END};

combo_t key_combos[] = {
    [CYRILLIC_HA] = COMBO(ha_combo, RU_HA),
    [CYRILLIC_HARD_SIGN] = COMBO(hard_sign_combo, RU_HARD),
    [SEMICOLON] = COMBO(semicolon_combo, EN_SCLN),
    [DOUBLE_QUOTE] = COMBO(double_quote_combo, EN_DQUO),
    // The K03 uses Backslash for this combo, rather than the Russian PC Ё
    // alias.
    [CYRILLIC_YO] = COMBO(yo_combo, KC_BSLS),
    [EXCLAMATION] = COMBO(exclamation_combo, KC_EXLM),
    [BACKSLASH] = COMBO(backslash_combo, EN_BSLS),
    [THUMB_SHIFT_ENTER] = COMBO(thumb_shift_enter_combo, LSFT(KC_ENT)),
    [THUMB_COMMAND_ENTER] = COMBO(thumb_command_enter_combo, LGUI(KC_ENT)),
    [THUMB_ALT] = COMBO(thumb_alt_combo, KC_RALT),
    [THUMB_COMMAND_BACKSPACE] = COMBO(thumb_command_backspace_combo, LGUI(KC_BSPC)),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(PIANO)) {
        return false;
    }
    switch (combo_index) {
    case THUMB_SHIFT_ENTER:
    case THUMB_COMMAND_ENTER:
    case THUMB_ALT:
    case THUMB_COMMAND_BACKSPACE:
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

// A key override also works when Command was held before Backspace was pressed.
const key_override_t word_delete_override = ko_make_with_layers_negmods_and_options(
    MOD_MASK_GUI, KC_BSPC, LALT(KC_BSPC), ~0, 0, ko_options_default | ko_option_no_reregister_trigger);
const key_override_t *key_overrides[] = {&word_delete_override};

static void start_piano(void) {
    layer_on(PIANO);
    PLAY_SONG(piano_start_song);
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
            start_piano();
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
            start_piano();
            // QMK looks up this key again after the layer changes.
            return true;
        }
    }
    // Handle the red keys before QMK buffers them for combos.
    if (keycode == MO(APPS) || keycode == MO(NAV)) {
        const uint8_t layer = QK_MOMENTARY_GET_LAYER(keycode);
        if (record->event.pressed) {
            layer_on(layer);
        } else {
            layer_off(layer);
        }
    }
    return true;
}

static void hello_kotify(void) {
    PLAY_SONG(hello_kotify_song);
    const saved_mods_t mods = save_and_clear_mods();
    select_input_source(false);
    tap_code16(APP(KC_G));
    wait_ms(50);
    tap_code(KC_ESC);
    tap_code(KC_ESC);
    tap_code16(LGUI(KC_F));
    wait_ms(50);
    SEND_STRING_DELAY("kotify ser", TAP_CODE_DELAY);
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
    select_input_source(is_russian() && english_symbols_held == 0);
    restore_mods(mods);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= EN_DOT && keycode <= EN_BSLS) {
        const uint16_t output = pgm_read_word(&english_symbols[keycode - EN_DOT]);
        if (record->event.pressed) {
            if (english_symbols_held++ == 0 && is_russian()) {
                select_input_source(false);
            }
            register_code16(output);
        } else {
            unregister_code16(output);
            if (english_symbols_held > 0 && --english_symbols_held == 0 && is_russian()) {
                select_input_source(true);
            }
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
    case MO(APPS):
    case MO(NAV):
        // The physical press and release already updated the layer.
        return false;
    case LGUI(KC_BSPC):
    case LGUI(KC_ENT):
    case KC_RALT:
        // When a combo uses a red key, drop its layer before sending the shortcut.
        if (IS_COMBOEVENT(record->event) && record->event.pressed) {
            layer_off(keycode == LGUI(KC_BSPC) ? APPS : NAV);
        }
        return true;
    case LANG_SWITCH:
        if (record->event.pressed) {
            set_language(!is_russian());
        }
        return false;
    case HELLO_KOTIFY:
        if (record->event.pressed) {
            hello_kotify();
        }
        return false;
    case HOLD_LOCK:
        lock_held = record->event.pressed;
        if (lock_held) {
            lock_timer = timer_read();
            lock_sent = false;
        }
        return false;
    case UNUSED_BE:
    case UNUSED_E:
        // These otherwise empty English positions still take part in combos.
        return false;
    default:
        return true;
    }
}

void matrix_scan_user(void) {
    if (piano_key_held && !layer_state_is(PIANO) && timer_elapsed32(piano_key_timer) >= PIANO_HOLD_MS) {
        piano_taps = 0;
        start_piano();
    }
    if (lock_held && !lock_sent && timer_elapsed(lock_timer) >= 1000) {
        const saved_mods_t mods = save_and_clear_mods();
        tap_code16(LGUI(LCTL(KC_Q)));
        restore_mods(mods);
        lock_sent = true;
    }
}
