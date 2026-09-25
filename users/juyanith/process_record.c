
#include "juyanith.h"

#include "primary_editing.h"

// Shift/Alt select editing actions; consume those selectors in the output,
// then restore physical/weak modifiers so subsequent keys keep their state.
static void tap_primary_editing(uint16_t action) {
    const uint8_t mods = get_mods();
    const uint8_t weak = get_weak_mods();
    const uint8_t selectors = MOD_MASK_SHIFT | MOD_MASK_ALT;
    const uint8_t active = mods | weak;
    const uint16_t key = primary_editing_key(action, is_apple_os(), active & MOD_MASK_SHIFT, active & MOD_MASK_ALT);
    if (key == KC_NO) return;
    // This tap bypasses the later override processor. End a held movement
    // first so its replacement modifiers cannot leak into the editor command.
    if (key_override_is_enabled()) {
        key_override_off();
        key_override_on();
    }
    set_mods(mods & ~selectors);
    set_weak_mods(weak & ~selectors);
    tap_code16(key);
    set_mods(mods);
    set_weak_mods(weak);
    send_keyboard_report();
}

static uint8_t delete_saved_mods;
static uint8_t delete_saved_weak_mods;
static uint16_t delete_key;
static uint8_t delete_word_mod;

static void start_primary_delete(void) {
    const uint8_t mods = get_mods();
    const uint8_t weak = get_weak_mods();
    const uint8_t active = mods | weak;
    const bool shift = active & MOD_MASK_SHIFT;
    const bool alt = active & MOD_MASK_ALT;

    delete_saved_mods = mods;
    delete_saved_weak_mods = weak;
    delete_key = shift ? KC_DEL : KC_BSPC;
    delete_word_mod = alt ? (is_apple_os() ? MOD_LALT : MOD_LCTL) : 0;

    if (key_override_is_enabled()) {
        key_override_off();
        key_override_on();
    }
    set_mods(mods & ~(MOD_MASK_SHIFT | MOD_MASK_ALT));
    set_weak_mods(weak & ~(MOD_MASK_SHIFT | MOD_MASK_ALT));
    if (delete_word_mod) register_mods(delete_word_mod);
    register_code(delete_key);
    send_keyboard_report();
}

static void stop_primary_delete(void) {
    unregister_code(delete_key);
    if (delete_word_mod) unregister_mods(delete_word_mod);
    set_mods(delete_saved_mods);
    set_weak_mods(delete_saved_weak_mods);
    send_keyboard_report();
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t* record)
{
    prepare_primary_movement();
    switch (keycode) {
        case MT_UNDO:
        case MT_CUT:
        case MT_COPY:
        case MT_PSTE:
        case MT_RCTL:
            if (!record->tap.count) return true; // Preserve QMK modifier holds.
            // Tap actions use the same resolver as the immediate editing keys.
        case NV_LOC:
        case NV_FIND:
            if (record->event.pressed) tap_primary_editing(keycode);
            return false;

        case NV_BSDL:
            if (record->event.pressed) {
                start_primary_delete();
            } else {
                stop_primary_delete();
            }
            return false;

        case NV_LEFT:
        case NV_RGHT:
        case NV_HOME:
        case NV_END:
        case NV_PGUP:
        case NV_PGDN:
        case NV_CURS:
            return true; // QMK key overrides handle held movement and release.

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

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT_UNDO:
        case MT_CUT:
        case MT_COPY:
        case MT_PSTE:
            return true;
        default:
            return false;
    }
}
