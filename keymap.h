// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include QMK_KEYBOARD_H

enum layers {
    EN_BASE,
    RU_BASE,
    APP_NAV,
    NUMBERS,
    SYMBOLS,
    SYSTEM,
    PIANO,
    LAYER_COUNT,
};

// Each EN_x key types KC_x with the English input source, even in Russian.
// This one list generates both the EN_x keycodes and their KC_x outputs.
// clang-format off
#define ENGLISH_SYMBOLS(X) \
    X(DOT)  X(COMM) X(COLN) X(GRV)  X(QUOT) X(QUES) X(TILD) \
    X(LT)   X(GT)   X(LCBR) X(RCBR) X(ASTR) X(PERC) X(LBRC) \
    X(RBRC) X(AT)   X(DLR)  X(HASH) X(CIRC) X(PIPE) X(AMPR) \
    X(SCLN) X(DQUO) X(SLSH) X(BSLS)
// clang-format on

enum custom_keycodes {
    LANG_EN = SAFE_RANGE,
    LANG_RU,
    HELLO_KOTIFY,
    FLASH_KEYMAPP,
    HOLD_LOCK,
    UNUSED_E,
#define X(name) EN_##name,
    ENGLISH_SYMBOLS(X)
#undef X
    PIANO_KEY,
    PIANO_NOTE,
    COMMA_SPACE,
    APP_NAV_KEY,
};

#define APP(key) LGUI(LCTL(LALT(key)))

// EN_DOT and EN_BSLS are the first and last entries of ENGLISH_SYMBOLS.
static inline bool is_english_symbol(uint16_t keycode) { return keycode >= EN_DOT && keycode <= EN_BSLS; }

static inline bool is_number_key(uint16_t keycode) { return keycode >= KC_1 && keycode <= KC_0; }
static inline bool is_punctuation_key(uint16_t keycode) { return keycode >= KC_MINUS && keycode <= KC_SLASH; }

bool is_letter(uint16_t keycode, bool russian);
