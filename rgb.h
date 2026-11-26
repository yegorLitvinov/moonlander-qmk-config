// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>

void adjust_rgb_effect(uint16_t keycode);
void rgb_effects_scan(void);
void rgb_effect_keypress(uint8_t row, uint8_t col);
void render_heatmap(uint8_t led_min, uint8_t led_max, uint8_t flags);
void render_quick_fade(uint8_t led_min, uint8_t led_max, uint8_t flags);
void render_finger_zones(uint8_t led_min, uint8_t led_max);
