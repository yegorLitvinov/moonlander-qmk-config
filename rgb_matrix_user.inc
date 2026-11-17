// SPDX-License-Identifier: GPL-2.0-or-later
RGB_MATRIX_EFFECT(FINGER_ZONES)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "rgb.h"

static bool FINGER_ZONES(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    render_finger_zones(led_min, led_max);
    return rgb_matrix_check_finished_leds(led_max);
}
#endif
