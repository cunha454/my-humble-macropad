#include QMK_KEYBOARD_H

#define KNOB_BTN_PIN GP2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x4(
        LCTL(LSFT(KC_C)), LCTL(LSFT(KC_V)), LCTL(LALT(KC_T)), LGUI(KC_D),
        KC_MPLY, KC_MNXT, KC_PSCR, LCTL(KC_D)
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_GREEN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 1);
}

void matrix_scan_user(void) {
    static bool last = true;
    static uint16_t last_change = 0;

    bool now = gpio_read_pin(KNOB_BTN_PIN);
    if (now != last && timer_elapsed(last_change) > 20) {
        last_change = timer_read();
        last = now;
        if (!now) {
            tap_code(KC_MUTE);
        }
    }
}

