#include "juyanith.h"

void leader_end_user(void) {
    if (leader_sequence_one_key(QK_LEAD)) {
        return;                                         // cancel leader
    }

    if (leader_sequence_one_key(KC_A)) {                // select all occurrences
        tap_primary_mods(KC_L, MOD_LSFT);
        return;
    }
    if (leader_sequence_two_keys(KC_A, KC_A)) {         // select all
        tap_primary(KC_A);
        return;
    }

    if (leader_sequence_one_key(KC_B)) {                // build
        tap_primary_mods(KC_B, MOD_LSFT);
        return;
    }

    if (leader_sequence_one_key(KC_BSLS)) {             // insert
        tap_code16(KC_INS);                             // NOTE: this doesn't work on mac
        return;
    }

    if (leader_sequence_one_key(KC_D)) {                // select word
        tap_primary(KC_D);
        return;
    }
    if (leader_sequence_two_keys(KC_D, KC_D)) {         // select line
        tap_primary(KC_L);
        return;
    }

    if (leader_sequence_one_key(KC_DOT)) {              // code suggestions
        tap_primary(KC_DOT);
        return;
    }

    if (leader_sequence_one_key(KC_F)) {                // find
        tap_primary(KC_F);
        return;
    }
    if (leader_sequence_two_keys(KC_F, KC_F)) {         // replace
        tap_primary_mods(KC_F, MOD_LALT);
        return;
    }
    if (leader_sequence_two_keys(KC_F, KC_R)) {         // find references
        tap_mods(KC_F12, MOD_LSFT);
        return;
    }

    if (leader_sequence_one_key(KC_G)) {                // goto line
        tap_mods(KC_G, MOD_LCTL);
        return;
    }
    if (leader_sequence_two_keys(KC_G, KC_G)) {         // goto definition
        tap_code16(KC_F12);
        return;
    }
    if (leader_sequence_two_keys(KC_G, KC_F)) {         // goto? references
        tap_mods(KC_F12, MOD_LSFT);
        return;
    }

    if (leader_sequence_one_key(KC_M)) {                // maximize toggle
        if (is_apple_os()) {
            tap_mods(KC_F, MOD_LGUI | MOD_LCTL);
        } else {
            tap_mods(KC_UP, MOD_LGUI);
        }
        return;
    }
    if (leader_sequence_two_keys(KC_M, KC_M)) {         // minimize
        if (is_apple_os()) {
            tap_mods(KC_M, MOD_LGUI);
        } else {
            tap_mods(KC_DOWN, MOD_LGUI);
        }
        return;
    }

    if (leader_sequence_one_key(KC_N)) {                // new
        tap_primary(KC_N);
        return;
    }
    if (leader_sequence_two_keys(KC_N, KC_N)) {         // rename
        tap_code16(KC_F2);
        return;
    }

    if (leader_sequence_one_key(KC_O)) {                // open
        tap_primary(KC_O);
        return;
    }
    if (leader_sequence_two_keys(KC_O, KC_O)) {         // open symbols
        tap_primary_mods(KC_O, MOD_LSFT);
        return;
    }

    if (leader_sequence_one_key(KC_P)) {                // palette
        tap_primary(KC_P);
        return;
    }
    if (leader_sequence_two_keys(KC_P, KC_P)) {         // (command) palette
        tap_primary_mods(KC_P, MOD_LSFT);
        return;
    }

    if (leader_sequence_one_key(KC_R)) {                // run
        tap_code16(KC_F5);
        return;
    }
    if (leader_sequence_two_keys(KC_R, KC_R)) {         // run without debug
        tap_primary_mods(KC_F5, MOD_RCTL);
        return;
    }

    if (leader_sequence_one_key(KC_S)) {                // save
        tap_primary(KC_S);
        return;
    }
    if (leader_sequence_two_keys(KC_S, KC_S)) {         // save all
        tap_primary_mods(KC_S, MOD_LALT);
        return;
    }
    if (leader_sequence_two_keys(KC_S, KC_A)) {        // save as
        tap_primary_mods(KC_S, MOD_LSFT);
        return;
    }

    if (leader_sequence_one_key(KC_SPC)) {              // applications
        if (is_apple_os()) {
            tap_mods(KC_SPC, MOD_LGUI);
        } else {
            tap_code16(KC_LGUI);
        }
        return;
    }

    if (leader_sequence_one_key(KC_SLSH)) {             // line comment
        tap_primary(KC_SLSH);
        return;
    }
    if (leader_sequence_two_keys(KC_SLSH, KC_SLSH)) {   // block comment
        tap_primary_mods(KC_A, MOD_LSFT | MOD_LALT);
        return;
    }

    if (leader_sequence_one_key(KC_T)) {                // terminal (editor)
        tap_mods(KC_GRV, MOD_LCTL);
        return;
    }
    if (leader_sequence_two_keys(KC_T, KC_T)) {         // terminal (system)
        tap_hyper(KC_T);
        return;
    }

    if (leader_sequence_one_key(KC_W)) {                // window close
        if (is_apple_os()) {
            tap_mods(KC_W, MOD_LGUI);
        } else {
            tap_mods(KC_F4, MOD_LALT);
        }
        return;
    }
    if (leader_sequence_two_keys(KC_W, KC_E)) {         // window editor (linux -> ?, mac -> zed, windows -> vscode)
        tap_hyper(KC_E);
        return;
    }
    if (leader_sequence_two_keys(KC_W, KC_F)) {         // window files (linux -> files, mac -> finder, windows -> explorer)
        tap_hyper(KC_F);
        return;
    }
    if (leader_sequence_two_keys(KC_W, KC_T)) {         // window terminal (linux -> term, mac -> ghostty, windows -> terminal)
        tap_hyper(KC_T);
        return;
    }
    if (leader_sequence_two_keys(KC_W, KC_W)) {         // window web browser (linux -> brave, mac -> safari, windows -> edge)
        tap_hyper(KC_W);
        return;
    }
}
