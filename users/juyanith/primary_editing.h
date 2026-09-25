#pragma once

// Resolve physical editing actions independently of tap/hold processing.
static inline uint16_t primary_editing_key(uint16_t action, bool apple, bool shift, bool alt) {
    uint16_t key = KC_NO;
    switch (action) {
        case NV_LEFT:
        case NV_RGHT:
            key = action == NV_LEFT ? KC_LEFT : KC_RGHT;
            if (alt) key = apple ? A(key) : C(key);
            break;
        case NV_HOME:
        case NV_END:
            key = action == NV_HOME ? KC_HOME : KC_END;
            if (alt) key = apple ? G(action == NV_HOME ? KC_UP : KC_DOWN) : C(key);
            else if (apple) key = G(action == NV_HOME ? KC_LEFT : KC_RGHT);
            break;
        case NV_PGUP: key = KC_PGUP; break;
        case NV_PGDN: key = KC_PGDN; break;
        case NV_BSDL:
            key = shift ? KC_DEL : KC_BSPC;
            return alt ? (apple ? A(key) : C(key)) : key;
        case NV_FIND:
            return alt ? (apple ? G(A(KC_F)) : C(KC_H))
                       : (apple ? G(KC_F) : C(KC_F));
        case NV_CURS:
            if (alt) return shift ? S(apple ? G(KC_D) : C(KC_D))
                                  : (apple ? G(KC_D) : C(KC_D));
            key = shift ? KC_UP : KC_DOWN;
            return apple ? G(A(key)) : A(S(key));
        case NV_LOC:
            return apple ? (shift ? G(S(KC_MINS)) : G(KC_MINS))
                         : (shift ? C(S(KC_MINS)) : C(A(KC_MINS)));
        case MT_RCTL:
            key = apple ? G(KC_F3) : C(KC_F3);
            break;
        case MT_RCMD: return KC_BSLS;
        case MT_UNDO:
            return apple ? (shift ? G(S(KC_Z)) : G(KC_Z))
                         : (shift ? C(KC_Y) : C(KC_Z));
        case MT_CUT: return apple ? G(KC_X) : C(KC_X);
        case MT_COPY: return apple ? G(KC_C) : C(KC_C);
        case MT_PSTE: return apple ? G(KC_V) : C(KC_V);
        case MT_RSFT: return KC_MINS;
        case MT_RALT: return KC_EQL;
        default: return KC_NO;
    }
    return shift ? S(key) : key;
}
