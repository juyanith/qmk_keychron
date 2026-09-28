
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

static bool process_system_modtap(uint16_t keycode, keyrecord_t *record) {
    if (get_highest_layer(layer_state) != SYSTEM_LAYER_INDEX) return false;
    uint16_t tap_key = KC_NO;
    switch (keycode) {
        case MT_CSFT: tap_key = LCAG(KC_C); break;
        case MT_MCTL: tap_key = LCAG(KC_M); break;
        case MT_CMAS: tap_key = LCAG(KC_COMM); break;
        case MT_DOTA: tap_key = LCAG(KC_DOT); break;
        case MT_SLSG: tap_key = LCAG(KC_SLSH); break;
        default: return false;
    }
    if (!record->tap.count || record->event.pressed) return false;
    tap_code16(tap_key);
    return true;
}

static void tap_hotkey(uint16_t keycode) {
    const uint8_t mods = get_mods();
    const uint8_t weak = get_weak_mods();
    const uint8_t active = mods | weak;
    const bool apple = is_apple_os();
    const bool shift = active & MOD_MASK_SHIFT;
    const bool alt = active & MOD_MASK_ALT;
    uint16_t key = KC_NO;

    switch (keycode) {
        case HK_WORD:   key = apple ? G(KC_D) : C(KC_D); break;
        case HK_LINE:   key = apple ? G(KC_L) : C(KC_L); break;
        case HK_FIND:   key = alt ? (apple ? G(A(KC_F)) : C(KC_H)) : (apple ? G(KC_F) : C(KC_F)); break;
        case HK_MATCH:
            key = apple ? G(S(KC_BSLS)) : C(S(KC_BSLS));
            if (alt || shift) key = A(key);
            break;
        case HK_BACK:   key = apple ? C(shift ? S(KC_MINS) : KC_MINS) : C(shift ? S(KC_MINS) : A(KC_MINS)); break;
        case HK_CURSOR: key = alt ? (apple ? A(G(KC_D)) : A(C(KC_D))) : (apple ? G(A(shift ? KC_UP : KC_DOWN)) : A(S(shift ? KC_UP : KC_DOWN))); break;
        case HK_OCCUR:  key = apple ? G(KC_F3) : C(KC_F3); break;
        case HK_SHRINK: key = apple ? C(S(G(KC_LEFT))) : A(S(KC_LEFT)); break;
        case HK_GROW:   key = apple ? C(S(G(KC_RGHT))) : A(S(KC_RGHT)); break;
        case SYS_LOCK_KEY: key = apple ? G(C(KC_Q)) : LCAG(KC_Q); break;
        case SYS_SHOT: key = apple ? G(S(KC_3)) : KC_PSCR; break;
        default: return;
    }
    const uint8_t selectors = keycode == HK_OCCUR ? MOD_MASK_ALT : (MOD_MASK_SHIFT | MOD_MASK_ALT);
    set_mods(mods & ~selectors);
    set_weak_mods(weak & ~selectors);
    send_keyboard_report();
    tap_code16(key);
    set_mods(mods);
    set_weak_mods(weak);
    send_keyboard_report();
}

bool process_record_juyanith(uint16_t keycode, keyrecord_t* record)
{
    prepare_primary_movement();
    if (process_system_modtap(keycode, record)) return false;
    switch (keycode) {
        case MT_UNDO:
        case MT_CUT:
        case MT_COPY:
        case MT_PSTE:
        case MT_RCTL:
            if (!record->tap.count) return true; // Preserve QMK modifier holds.
            if (record->event.pressed) return true;
            // Emit completed taps on release; holds remain native QMK mod-taps.
            tap_primary_editing(keycode);
            return false;
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

        case HK_WORD:
        case HK_LINE:
        case HK_MATCH:
        case HK_CURSOR:
        case HK_BACK:
        case HK_OCCUR:
        case HK_SHRINK:
        case HK_GROW:
            if (record->event.pressed) tap_hotkey(keycode);
            return false;

        case SYS_LOCK_KEY:
        case SYS_SHOT:
            if (record->event.pressed) tap_hotkey(keycode);
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
        case CAPS_HK:
        case ENT_HK:
        case MT_UNDO:
        case MT_CUT:
        case MT_COPY:
        case MT_PSTE:
            return true;
        default:
            return false;
    }
}
