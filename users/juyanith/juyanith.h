#pragma once

#include QMK_KEYBOARD_H
#include "os_detection.h"

#define SPC_SYM LT(SYMBOL, KC_SPC)
#define CAPS_HK LCAG_T(KC_ESC)
#define ENT_HK LCAG_T(KC_ENT)
#define TAB_HYPR HYPR_T(KC_TAB)
#define FN_MAC MO(MAC_FN)
#define FN_WIN MO(WIN_FN)

/* MAC_BASE home-row mods: secondary, alt, primary, shift. */
#define HRM_A LCTL_T(KC_A)
#define HRM_S LALT_T(KC_S)
#define HRM_D LGUI_T(KC_D)
#define HRM_F LSFT_T(KC_F)
#define HRM_J RSFT_T(KC_J)
#define HRM_K RGUI_T(KC_K)
#define HRM_L RALT_T(KC_L)
#define HRM_SEMI RCTL_T(KC_SCLN)

/* SYMBOL home-row mods keep the same physical modifier positions. */
#define SYM_A LCTL_T(KC_1)
#define SYM_S LALT_T(KC_2)
#define SYM_D LGUI_T(KC_3)
#define SYM_F LSFT_T(KC_4)
#define SYM_J RSFT_T(KC_LEFT)
#define SYM_K RGUI_T(KC_DOWN)
#define SYM_L RALT_T(KC_UP)
#define SYM_SEMI RCTL_T(KC_RGHT)

#define RE_NAME KC_F2
#define RUN_CNT KC_F5
#define TOG_BRP KC_F9
#define STEP_IN KC_F11
#define STEP_OT LSFT(KC_F11)
#define STEP_OV KC_F10
#define SHS(k) LSFT(k)

enum custom_keycodes {
    SYM_SHOT = SAFE_RANGE,
    SYM_UNDO,
    SYM_CUT,
    SYM_COPY,
    SYM_PSTE,
};

static inline bool is_apple_os(void) {
    const os_variant_t os = detected_host_os();
    return os == OS_MACOS || os == OS_IOS;
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t *record);
