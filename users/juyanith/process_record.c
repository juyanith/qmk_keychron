#include "juyanith.h"

bool process_record_juyanith(uint16_t keycode, keyrecord_t *record) {
    if (keycode == SYM_SHOT && record->event.pressed) {
        tap_code16(is_apple_os() ? G(S(KC_3)) : KC_PSCR);
        return false;
    }
    return true;
}
