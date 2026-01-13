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
#define SPC_NAV LT(NAV_LT, KC_SPC)
#define WRD_PRV LALT(KC_LEFT)
#define WRD_NXT LALT(KC_RGHT)
#define RE_NAME KC_F2
#define RUN_CNT KC_F5
#define TOG_BRP KC_F9
#define STEP_IN KC_F11
#define STEP_OT LSFT(KC_F11)
#define STEP_OV KC_F10
#define MT_UNDO LGUI_T(KC_0) // KC_Z
#define MT_CUT  LALT_T(KC_0) // KC_X
#define MT_COPY LSFT_T(KC_0) // KC_C
#define MT_PSTE LCTL_T(KC_0) // KC_V
#define MT_LBCK LCTL_T(KC_1) // C(KC_MINS)
#define MT_CRDN LSFT_T(KC_1) // G(A(KC_DOWN))
#define MT_CRUP LALT_T(KC_1) // G(A(KC_UP))
#define MT_LFWD LGUI_T(KC_1) // C(S(KC_MINS))

enum custom_keycodes {
    KC_LCAG = SAFE_RANGE,
    DOC_PRV,
    DOC_NXT,
    LINE_DN,
    LINE_UP,
    MV_MTCH,
};

static inline bool is_apple_os(void) {
    os_variant_t detected_os = detected_host_os();
    return detected_os == OS_MACOS
        || detected_os == OS_IOS;
}

// Helper: send "primary modifier" = Cmd on mac, Ctrl on win/linux
static inline uint8_t primary_mod(void) {
    return is_apple_os() ? MOD_LGUI : MOD_LCTL;
}

static inline void tap_mods(uint16_t key, uint8_t mods) {
    register_mods(mods);
    tap_code16(key);
    unregister_mods(mods);
}

static inline void tap_hyper(uint16_t key) {
    tap_mods(key, MOD_LCTL | MOD_LALT | MOD_LGUI | MOD_LSFT);
}

static inline void tap_super(uint16_t key) {
    tap_mods(key, MOD_LCTL | MOD_LALT | MOD_LGUI);
}

static inline void tap_primary(uint16_t key) {
    tap_mods(key, primary_mod());
}

static inline void tap_primary_mods(uint16_t key, uint8_t mods) {
    tap_mods(key, primary_mod() | mods);
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t* record);
