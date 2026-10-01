#include "juyanith.h"

static uint16_t symbol_shortcut(uint16_t keycode) {
    switch (keycode) {
        case SYM_UNDO: return is_apple_os() ? G(KC_Z) : C(KC_Z);
        case SYM_CUT:  return is_apple_os() ? G(KC_X) : C(KC_X);
        case SYM_COPY: return is_apple_os() ? G(KC_C) : C(KC_C);
        case SYM_PSTE: return is_apple_os() ? G(KC_V) : C(KC_V);
        default:       return KC_NO;
    }
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    if (keycode == SYM_SHOT) {
        tap_code16(is_apple_os() ? G(S(KC_3)) : KC_PSCR);
        return false;
    }
    const uint16_t shortcut = symbol_shortcut(keycode);
    if (shortcut != KC_NO) {
        tap_code16(shortcut);
        return false;
    }
    return true;
}
