// SPDX-License-Identifier: GPL-2.0-or-later
// Preserve the mode order saved by earlier firmware.
RGB_MATRIX_EFFECT(HEATMAP)
RGB_MATRIX_EFFECT(QUICK_FADE)
RGB_MATRIX_EFFECT(FINGER_ZONES)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "rgb.h"

static bool HEATMAP(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    render_heatmap(led_min, led_max, params->flags);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool QUICK_FADE(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    render_quick_fade(led_min, led_max, params->flags);
    return rgb_matrix_check_finished_leds(led_max);
}

static bool FINGER_ZONES(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    render_finger_zones(led_min, led_max);
    return rgb_matrix_check_finished_leds(led_max);
}
#endif
