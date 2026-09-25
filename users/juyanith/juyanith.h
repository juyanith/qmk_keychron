#pragma once

#include QMK_KEYBOARD_H
#include "os_detection.h"

#define MT_ZGUI MT(MOD_LGUI, KC_Z)
#define MT_XALT MT(MOD_LALT, KC_X)
#define MT_CSFT MT(MOD_LSFT, KC_C)
#define MT_VCTL MT(MOD_LCTL, KC_V)
#define MT_MCTL MT(MOD_RCTL, KC_M)
#define MT_CMAS MT(MOD_RSFT, KC_COMM)
#define MT_DOTA MT(MOD_RALT, KC_DOT)
#define MT_SLSG MT(MOD_RGUI, KC_SLSH)
#define SPC_NAV LT(NV_LT, KC_SPC)
#define RE_NAME KC_F2
#define RUN_CNT KC_F5
#define TOG_BRP KC_F9
#define STEP_IN KC_F11
#define STEP_OT LSFT(KC_F11)
#define STEP_OV KC_F10
#define MT_LCAG LCAG_T(KC_ESC)
#define TAB_HYPR HYPR_T(KC_TAB)
#define MT_UNDO LGUI_T(KC_0) // KC_Z
#define MT_CUT  LALT_T(KC_0) // KC_X
#define MT_COPY LSFT_T(KC_0) // KC_C
#define MT_PSTE LCTL_T(KC_0) // KC_V
#define MT_RCTL RCTL_T(KC_F3)
#define MT_RSFT RSFT_T(KC_MINS) // Minus on tap; retain Right Shift hold
#define MT_RALT RALT_T(KC_EQL) // Equals on tap; retain Right Alt hold
#define MT_RCMD RGUI_T(KC_BSLS) // Backslash on tap; retain Right Command/Super hold

enum custom_keycodes {
    KC_LCAG = SAFE_RANGE,
    WRD_PRV,
    WRD_NXT,
    LINE_DN,
    LINE_UP,
    MV_MTCH,
    NV_LOC,
    NV_FIND,
    NV_LEFT,
    NV_RGHT,
    NV_DOWN,
    NV_UP,
    NV_HOME,
    NV_END,
    NV_PGUP,
    NV_PGDN,
    NV_BSDL,
    NV_CURS,
};

static inline void tap_hyper(uint16_t key) {
    tap_code16(C(A(G(S(key)))));
}

static inline void tap_super(uint16_t key) {
    tap_code16(C(A(G(key))));
}

static inline bool is_apple_os(void) {
    os_variant_t detected_os = detected_host_os();
    return detected_os == OS_MACOS
        || detected_os == OS_IOS;
}

// Helper: determine "primary modifier": Cmd on mac, Ctrl on win/linux
static inline uint8_t primary_mod(void) {
    return is_apple_os() ? MOD_LGUI : MOD_LCTL;
}

static inline void tap_primary(uint16_t key) {
    if (is_apple_os()) {
        tap_code16(G(key));
    } else {
        tap_code16(C(key));
    }
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t* record);

void prepare_primary_movement(void);
