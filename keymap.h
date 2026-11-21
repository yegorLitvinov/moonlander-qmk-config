// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include QMK_KEYBOARD_H

enum layers {
    EN_BASE,
    RU_BASE,
    APP_NAV,
    NUMBERS,
    SYMBOLS_EN,
    SYMBOLS_RU,
    SYSTEM,
    PIANO,
};

enum custom_keycodes {
    LANG_EN = SAFE_RANGE,
    LANG_RU,
    HELLO_KOTIFY,
    HOLD_LOCK,
    UNUSED_E,
    EN_DOT,
    EN_COMM,
    EN_COLN,
    EN_GRV,
    EN_QUOT,
    EN_QUES,
    EN_TILD,
    EN_LT,
    EN_GT,
    EN_EQL,
    EN_LCBR,
    EN_RCBR,
    EN_PLUS,
    EN_ASTR,
    EN_PERC,
    EN_LBRC,
    EN_RBRC,
    EN_AT,
    EN_DLR,
    EN_HASH,
    EN_CIRC,
    EN_PIPE,
    EN_AMPR,
    EN_SCLN,
    EN_DQUO,
    EN_MINS,
    EN_SLSH,
    EN_BSLS,
    PIANO_KEY,
    PIANO_NOTE,
    COMMA_SPACE,
    APP_NAV_KEY,
};

#define APP(key) LGUI(LCTL(LALT(key)))

static inline bool is_number_key(uint16_t keycode) { return keycode >= KC_1 && keycode <= KC_0; }
static inline bool is_punctuation_key(uint16_t keycode) { return keycode >= KC_MINUS && keycode <= KC_SLASH; }

bool is_letter(uint16_t keycode, bool russian);
