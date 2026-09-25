// Host-side resolver test: cc -std=c99 -Wall -Wextra -Werror this_file -o /tmp/primary-test
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
// Independent compact key/mod encodings for testing the pure resolver.
enum { KC_NO, KC_LEFT, KC_RGHT, KC_DOWN, KC_UP, KC_HOME, KC_END,
       KC_PGUP, KC_PGDN, KC_DEL, KC_BSPC, KC_GRV, KC_MINS, KC_EQL, KC_F3,
       KC_F, KC_H, KC_D, KC_BSLS, KC_Z, KC_Y, KC_X, KC_C, KC_V };
#define S(k) ((k) | 0x100)
#define A(k) ((k) | 0x200)
#define C(k) ((k) | 0x400)
#define G(k) ((k) | 0x800)
enum { NV_LEFT, NV_RGHT, NV_DOWN, NV_UP, NV_HOME, NV_END,
       NV_PGUP, NV_PGDN, NV_BSDL, NV_LOC, NV_FIND, NV_CURS,
       MT_RCTL, MT_RCMD, MT_UNDO, MT_CUT, MT_COPY, MT_PSTE, MT_RSFT, MT_RALT };
#include "../primary_editing.h"
struct test_case { uint16_t action; uint16_t mac[4]; uint16_t other[4]; };
// Columns: base, Shift, Alt, Alt+Shift.
static const struct test_case cases[] = {
 {NV_LEFT, {KC_LEFT,S(KC_LEFT),A(KC_LEFT),S(A(KC_LEFT))}, {KC_LEFT,S(KC_LEFT),C(KC_LEFT),S(C(KC_LEFT))}},
 {NV_RGHT,{KC_RGHT,S(KC_RGHT),A(KC_RGHT),S(A(KC_RGHT))}, {KC_RGHT,S(KC_RGHT),C(KC_RGHT),S(C(KC_RGHT))}},
 {NV_DOWN, {KC_DOWN,S(KC_DOWN),C(KC_PGDN),KC_NO}, {KC_DOWN,S(KC_DOWN),C(KC_DOWN),KC_NO}},
 {NV_UP,   {KC_UP,S(KC_UP),C(KC_PGUP),KC_NO}, {KC_UP,S(KC_UP),C(KC_UP),KC_NO}},
 {NV_HOME, {G(KC_LEFT),S(G(KC_LEFT)),G(KC_UP),S(G(KC_UP))}, {KC_HOME,S(KC_HOME),C(KC_HOME),S(C(KC_HOME))}},
 {NV_END, {G(KC_RGHT),S(G(KC_RGHT)),G(KC_DOWN),S(G(KC_DOWN))}, {KC_END,S(KC_END),C(KC_END),S(C(KC_END))}},
 {NV_PGUP,{KC_PGUP,S(KC_PGUP),KC_PGUP,S(KC_PGUP)}, {KC_PGUP,S(KC_PGUP),KC_PGUP,S(KC_PGUP)}},
 {NV_PGDN,{KC_PGDN,S(KC_PGDN),KC_PGDN,S(KC_PGDN)}, {KC_PGDN,S(KC_PGDN),KC_PGDN,S(KC_PGDN)}},
 {NV_BSDL,{KC_BSPC,KC_DEL,A(KC_BSPC),A(KC_DEL)}, {KC_BSPC,KC_DEL,C(KC_BSPC),C(KC_DEL)}},
 {NV_FIND,{G(KC_F),G(KC_F),G(A(KC_F)),G(A(KC_F))}, {C(KC_F),C(KC_F),C(KC_H),C(KC_H)}},
 {NV_CURS,{G(A(KC_DOWN)),G(A(KC_UP)),G(KC_D),S(G(KC_D))}, {A(S(KC_DOWN)),A(S(KC_UP)),C(KC_D),S(C(KC_D))}},
 {NV_LOC,{G(KC_MINS),G(S(KC_MINS)),G(KC_MINS),G(S(KC_MINS))}, {C(A(KC_MINS)),C(S(KC_MINS)),C(A(KC_MINS)),C(S(KC_MINS))}},
 {MT_RCTL,{G(KC_F3),S(G(KC_F3)),G(KC_F3),S(G(KC_F3))}, {C(KC_F3),S(C(KC_F3)),C(KC_F3),S(C(KC_F3))}},
 {MT_RCMD,{KC_BSLS,KC_BSLS,KC_BSLS,KC_BSLS}, {KC_BSLS,KC_BSLS,KC_BSLS,KC_BSLS}},
 {MT_UNDO,{G(KC_Z),G(S(KC_Z)),G(KC_Z),G(S(KC_Z))}, {C(KC_Z),C(KC_Y),C(KC_Z),C(KC_Y)}},
 {MT_CUT,{G(KC_X),G(KC_X),G(KC_X),G(KC_X)}, {C(KC_X),C(KC_X),C(KC_X),C(KC_X)}},
 {MT_COPY,{G(KC_C),G(KC_C),G(KC_C),G(KC_C)}, {C(KC_C),C(KC_C),C(KC_C),C(KC_C)}},
 {MT_PSTE,{G(KC_V),G(KC_V),G(KC_V),G(KC_V)}, {C(KC_V),C(KC_V),C(KC_V),C(KC_V)}},
 {MT_RSFT,{KC_MINS,KC_MINS,KC_MINS,KC_MINS}, {KC_MINS,KC_MINS,KC_MINS,KC_MINS}},
 {MT_RALT,{KC_EQL,KC_EQL,KC_EQL,KC_EQL}, {KC_EQL,KC_EQL,KC_EQL,KC_EQL}},
};
int main(void) {
 for (unsigned i=0;i<sizeof(cases)/sizeof(cases[0]);i++)
  for (unsigned mods=0;mods<4;mods++) {
   assert(primary_editing_key(cases[i].action,true,mods&1,mods&2)==cases[i].mac[mods]);
   assert(primary_editing_key(cases[i].action,false,mods&1,mods&2)==cases[i].other[mods]);
  }
 return 0;
}
