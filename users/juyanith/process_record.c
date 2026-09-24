
#include "juyanith.h"

// Shift selects an alternate action without extending a text selection.
static void tap_nav_shifted(uint16_t normal, uint16_t shifted) {
    const uint8_t mods = get_mods();
    const uint8_t weak_mods = get_weak_mods();
    const bool shift = ((mods | weak_mods) & MOD_MASK_SHIFT) != 0;
    set_mods(mods & ~MOD_MASK_SHIFT);
    set_weak_mods(weak_mods & ~MOD_MASK_SHIFT);
    tap_code16(shift ? shifted : normal);
    set_mods(mods);
    set_weak_mods(weak_mods);
    send_keyboard_report();
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode) {
        case NAV_LOC: // Forward location; Shift selects backward location
            if (record->event.pressed) {
                tap_nav_shifted(C(S(KC_MINS)), is_apple_os() ? C(KC_MINS) : C(A(KC_MINS)));
            }
            return false;

        case MT_UNDO: // LGUI on hold, [LCTL|LGUI]-z on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_primary(KC_Z);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_CUT: // LALT on hold, [LCTL|LGUI]-x on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_primary(KC_X);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_COPY: // LSFT on hold, [LCTL|LGUI]-c on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_primary(KC_C);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_PSTE: // LCTL on hold, [LCTL|LGUI]-v on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_primary(KC_V);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_INST: // Right Shift on hold; Cmd/Ctrl+F3 on tap
        case MT_ADD: // Right Alt on hold; Cmd/Ctrl+D on tap
        case MT_ARROW: // Right Super on hold; Down or unshifted Up on tap
            if (record->tap.count) {
                if (record->event.pressed) {
                    if (keycode == MT_ARROW) {
                        tap_nav_shifted(KC_DOWN, KC_UP);
                    } else {
                        tap_primary(keycode == MT_INST ? KC_F3 : KC_D);
                    }
                }
                return false;
            }
            break;

        case WRD_PRV: // Cmd+Left on macOS; Ctrl+Left elsewhere
            if (record->event.pressed) { // On press
                if (record->event.pressed) { // On press
                    if (is_apple_os()) {
                        tap_code16(G(KC_LEFT));
                    } else {
                        tap_code16(C(KC_LEFT));
                    }
                }
                return false;  // Skip default handling.
            }
            break;

        case WRD_NXT: // Cmd+Right on macOS; Ctrl+Right elsewhere
            if (record->event.pressed) { // On press
                if (record->event.pressed) { // On press
                    if (is_apple_os()) {
                        tap_code16(G(KC_RIGHT));
                    } else {
                        tap_code16(C(KC_RIGHT));
                    }
                }
                return false;  // Skip default handling.
            }
            break;

        case LINE_DN: // Custom: Move line down
            if (record->event.pressed) { // On press
                register_mods(MOD_LALT);
                register_code(KC_DOWN);
            } else {                     // On release
                unregister_code(KC_DOWN);
                unregister_mods(MOD_LALT);
            }
            return false;  // Skip default handling.
            break;

        case LINE_UP: // Custom: Move line up
            if (record->event.pressed) { // On press
                register_mods(MOD_LALT);
                register_code(KC_UP);
            } else {                     // On release
                unregister_code(KC_UP);
                unregister_mods(MOD_LALT);
            }
            return false;  // Skip default handling.
            break;

        case MV_MTCH: // Custom: Move next (MOD_PRIMARY-G)
            if (record->event.pressed) { // On press
                register_mods(primary_mod());
                register_code(KC_G);
            } else {                     // On release
                unregister_code(KC_G);
                unregister_mods(primary_mod());
            }
            return false;  // Skip default handling.
            break;
    }

    return true; // Continue default handling
}
