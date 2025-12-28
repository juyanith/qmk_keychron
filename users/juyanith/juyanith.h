#pragma once

#include QMK_KEYBOARD_H

#define MT_ZGUI MT(MOD_LGUI, KC_Z)
#define MT_XALT MT(MOD_LALT, KC_X)
#define MT_CSFT MT(MOD_LSFT, KC_C)
#define MT_VCTL MT(MOD_LCTL, KC_V)
#define MT_MCTL MT(MOD_RCTL, KC_M)
#define MT_CMAS MT(MOD_RSFT, KC_COMM)
#define MT_DOTA MT(MOD_RALT, KC_DOT)
#define MT_SLSG MT(MOD_RGUI, KC_SLSH)
#define SPC_NAV LT(NAV_LT, KC_SPC)
#define LOC_NXT LGUI(LSFT(KC_RBRC))
#define LOC_PRV LGUI(LSFT(KC_LBRC))
#define WRD_PRV LALT(KC_LEFT)
#define WRD_NXT LALT(KC_RGHT)
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
    DOC_NXT = SAFE_RANGE,
    DOC_PRV,
    LINE_UP,
    LINE_DN,
    MV_MTCH,
};

static inline bool is_macos(void) {
    return true; // TODO: Update this to actually detect OS
}

// Helper: send "primary modifier" = Cmd on mac, Ctrl on win/linux
static inline uint8_t primary_mod(void) {
    return is_macos() ? MOD_LGUI : MOD_LCTL;
}

static inline void tap_mods(uint16_t key, uint8_t mods) {
    register_mods(mods);
    tap_code16(key);
    unregister_mods(mods);
}

static inline void tap_hyper(uint16_t key) {
    tap_mods(key, MOD_LGUI | MOD_LALT | MOD_LSFT | MOD_LCTL);
}

static inline void tap_primary(uint16_t key) {
    tap_mods(key, primary_mod());
}

static inline void tap_primary_mods(uint16_t key, uint8_t mods) {
    tap_mods(key, primary_mod() | mods);
}
