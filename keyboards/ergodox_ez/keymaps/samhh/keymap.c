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
    CTRLW,
    FATLMB,
    THNLMB,
    HSOMAP,
    HSOAPL,
    EQNORM,
    EQJS,
    UQNORM,
    UQJS,
    UQHS,
    GBP,
    EUR
};

enum {
    TD_MQUOT,
    TD_CMMHY,
    TD_RSEXC,
    TD_PAREN,
    TD_SQBRK,
    TD_BRACE,
    TD_NGBRK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_ergodox(
        KC_AT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_LCMD,
        KC_QUES, KC_Q, KC_W, KC_E, KC_R, KC_T, TG(CODE),
        KC_UNDS, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, MO(CODE),
        KC_LCTL, KC_TILD, KC_BSLS, KC_PIPE, KC_ESC,
        KC_LCMD, KC_LALT,
        CTRLW,
        KC_SPC, KC_BSPC, KC_PERC,

        KC_RCMD, KC_6, KC_7, KC_8, KC_9, KC_0, KC_HASH,
        TG(MISC), KC_Y, KC_U, KC_I, KC_O, KC_P, KC_SLSH,
        KC_H, KC_J, KC_K, KC_L, TD(TD_MQUOT), KC_DLR,
        MO(MISC), KC_N, KC_M, TD(TD_CMMHY), KC_DOT, KC_QUES, TD(TD_RSEXC),
        KC_COLN, KC_SCLN, KC_EQL, KC_PLUS, KC_RCTL,
        KC_RALT, KC_RCMD,
        KC_DEL,
        KC_TAB, KC_ENT, MO(CODE)
    ),

    [CODE] = LAYOUT_ergodox(
        __, __, __, __, __, __, __,
        __, __, __, EQNORM, EQJS, __, __,
        __, HSOAPL, HSOMAP, THNLMB, FATLMB, __,
        __, __, UQHS, UQNORM, UQJS, __, __,
        __, __, __, __, __,
        __, __,
        __,
        __, __, __,

        __, __, __, __, __, __, __,
        __, __, __, __, __, __, __,
        __, TD(TD_PAREN), TD(TD_SQBRK), TD(TD_BRACE), TD(TD_NGBRK), __,
        __, __, __, __, __, __, __,
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
            case CTRLW:
                SEND_STRING(SS_LCTL("w"));
                break;
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
            case EQNORM:
                SEND_STRING("==");
                break;
            case EQJS:
                SEND_STRING("===");
                break;
            case UQNORM:
                SEND_STRING("!=");
                break;
            case UQJS:
                SEND_STRING("!==");
                break;
            case UQHS:
                SEND_STRING("/=");
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

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MQUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_GRV),
    [TD_CMMHY] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_MINS),
    [TD_RSEXC] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_EXLM),
    [TD_PAREN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_SQBRK] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_BRACE] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_NGBRK] = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK)
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

