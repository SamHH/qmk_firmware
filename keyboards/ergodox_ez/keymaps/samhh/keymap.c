#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0
#define CODE 1
#define MISC 2

// More readable noop alias
#define __ KC_NO

enum custom_keycodes {
    EPRM = SAFE_RANGE,
    VRSN,
    FATLMB,
    THNLMB,
    HSOMAP,
    HSOAPL,
    GBP,
    EUR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ergodox(
        __, KC_1, KC_2, KC_3, KC_4, KC_5, __,
        KC_QUES, KC_Q, KC_W, KC_E, KC_R, KC_T, MO(MISC),
        KC_UNDS, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(CODE),
        KC_LCTL, __, KC_GRV, KC_BSLS, KC_ESC,
        KC_LCMD, KC_LALT,
        __,
        KC_SPC, KC_BSPC, KC_TAB,

        __, KC_6, KC_7, KC_8, KC_9, KC_0, __,
        MO(MISC), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_SLSH,
        KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_DLR,
        MO(CODE), KC_N, KC_M, KC_COMM, KC_DOT, KC_MINS, KC_RSFT,
        KC_COLN, KC_SCLN, KC_EQL, __, KC_RCTL,
        KC_RALT, KC_RCMD,
        __,
        KC_TAB, KC_DEL, KC_ENT
    ),

    [CODE] = LAYOUT_ergodox(
        __, __, __, __, __, __, __,
        __, __, __, __, __, __, __,
        __, HSOAPL, HSOMAP, THNLMB, FATLMB, __,
        __, __, __, __, __, __, __,
        __, __, __, __, __,
        __, __,
        __,
        __, __, __,

        __, __, __, __, __, __, __,
        __, __, __, __, __, __, __,
        __, KC_LPRN, KC_LCBR, KC_LBRC, KC_LABK, __, __,
        __, KC_RPRN, KC_RCBR, KC_RBRC, KC_RABK, __,
        __, __, __, __, __,
        __, __,
        __,
        __, __, __
    ),

    [MISC] = LAYOUT_ergodox(
        KC_MUTE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_VOLU, __, KC_MPRV, KC_MPLY, KC_MNXT, __, __,
        KC_VOLD, __, KC_DLR, EUR, GBP, __,
        __, __, __, __, __, __, __,
        RESET, EEP_RST, VRSN, __, __,
        __, __,
        __,
        KC_BTN1, __, __,

        KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, __,
        __, __, __, __, __, __, KC_BRIU,
        KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, __, KC_BRID,
        __, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, __, __,
        __, __, __, __, __,
        __, __,
        __,
        __, __, KC_BTN2
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case EPRM:
                eeconfig_init();
                return false;
            case VRSN:
                SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                return false;
            case FATLMB:
                SEND_STRING("=>");
                break;
            case THNLMB:
                SEND_STRING("->");
                break;
            case HSOMAP:
                SEND_STRING("<$>");
                break;
            case HSOAPL:
                SEND_STRING("<*>");
                break;
            case GBP:
                SEND_STRING("£");
                break;
            case EUR:
                SEND_STRING("€");
                break;
        }
    }

    return true;
};

// Ergodox EZ LEDs:
//      1: Red
//      2: Green
//      3: Blue
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
            break;

        case 1:
            ergodox_right_led_3_on();
            break;

        case 2:
            ergodox_right_led_2_on();
            break;

        case 3:
            ergodox_right_led_1_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;

        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;

        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;

        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;

        default:
            break;
    }

    return state;
};

