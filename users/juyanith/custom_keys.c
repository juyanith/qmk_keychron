
#include "juyanith.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode) {
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

        case MT_LBCK: // LCTL on hold, LCTL-minus on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_mods(KC_MINUS, MOD_LCTL);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_CRDN: // LCTL on hold, LGUI-LALT-down on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_mods(KC_DOWN, MOD_LGUI | MOD_LALT);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_CRUP: // LCTL on hold, LGUI-LALT-up on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_mods(KC_UP, MOD_LGUI | MOD_LALT);
                }
                return false;  // Skip default handling.
            }
            break;

        case MT_LFWD: // LGUI on hold, LCTL-LSFT-minus on tap
            if (record->tap.count) { // On tap
                if (record->event.pressed) { // On press
                    tap_mods(KC_MINUS, MOD_LCTL | MOD_LSFT);
                }
                return false;  // Skip default handling.
            }
            break;

        case DOC_PRV: // Custom: Previous tab/document
            if (record->event.pressed) { // On press
                register_mods(primary_mod() | MOD_LSFT);
                register_code(KC_RBRC);
            } else {                     // On release
                unregister_code(KC_RBRC);
                unregister_mods(primary_mod() | MOD_LSFT);
            }
            return false;  // Skip default handling.
            break;

        case DOC_NXT: // Custom: Next tab/document
            if (record->event.pressed) { // On press
                register_mods(primary_mod() | MOD_LSFT);
                register_code(KC_LBRC);
            } else {                     // On release
                unregister_code(KC_LBRC);
                unregister_mods(primary_mod() | MOD_LSFT);
            }
            return false;  // Skip default handling.
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
                register_code(KC_DOWN);
            } else {                     // On release
                unregister_code(KC_DOWN);
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
