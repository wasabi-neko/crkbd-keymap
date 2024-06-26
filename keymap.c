/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "keycodes.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "oled.h"


// Layers
enum layer_names {
    L_QWERTY = 0,       // a normal layer for qwerty (with home row mods GASC)
    L_COLEMAK,          // a normal layer for colemak (with home tow mods GASC)
    L_GAME,             // a qwerty layer which without any tap dance
    L_GAME1,            // an alternative gaming layer
    L_GAME2,            // yet an alternative gaming layer
    L_NAVI,             // a multi-purpose layer for some quick navigation
    L_MOUSE,            //! not implemented yet
    L_NUM,              // a number layer
    L_SYM,              // a symbol layer
    L_GUI,              // a layer for GUI relative controls, e.g. moving a window around
    L_FUNCN,            // a layer for function-key and switching default layer e.g. colemak and game layer.
};

// Homerow mods for qwerty
#define QHOME_A LGUI_T(KC_A)
#define QHOME_S LALT_T(KC_S)
#define QHOME_D LSFT_T(KC_D)
#define QHOME_F LCTL_T(KC_F)

#define QHOME_J LCTL_T(KC_J)
#define QHOME_K LSFT_T(KC_K)
#define QHOME_L LALT_T(KC_L)
#define QHOME_SCLN LGUI_T(KC_SCLN)

// Homerow mods for colemak
#define CHOME_A LGUI_T(KC_A)
#define CHOME_R LALT_T(KC_R)
#define CHOME_S LSFT_T(KC_S)
#define CHOME_T LCTL_T(KC_T)

#define CHOME_N LCTL_T(KC_N)
#define CHOME_E LSFT_T(KC_E)
#define CHOME_I LALT_T(KC_I)
#define CHOME_O LGUI_T(KC_O)

// Hotkey keycode
#define NXTTAB LCTL(KC_PGDN)
#define PRVTAB LCTL(KC_PGUP)

#define WIN_LEFT LGUI(KC_LEFT)
#define WIN_UP LGUI(KC_UP)
#define WIN_DOWN LGUI(KC_DOWN)
#define WIN_RIGHT LGUI(KC_RIGHT)

#define DESK_UP LGUI(KC_PGUP)
#define DESK_DOWN LGUI(KC_PGDN)

// Macros
enum custom_keycodes {
    BACK_D = SAFE_RANGE         // parent directory; inputs: "../"
};


// Combos
const uint16_t PROGMEM kj_esc[] = {LSFT_T(KC_K), LCTL_T(KC_J), COMBO_END};
const uint16_t PROGMEM KJ_esc[] = {S(LSFT_T(KC_K)), S(LCTL_T(KC_J)), COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(kj_esc, KC_ESC),
    COMBO(KJ_esc, KC_ESC),
};


// Layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Normal layer
  //  use home row mods: GASC
  [L_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CW_TOGG, QHOME_A, QHOME_S, QHOME_D, QHOME_F,    KC_G,                         KC_H, QHOME_J, QHOME_K, QHOME_L,QHOME_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PSCR,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
            LT(L_GUI,KC_LGUI), LT(L_NUM,KC_TAB), LT(L_NAVI,KC_SPC),     KC_ENT, LT(L_SYM, KC_BSPC), MO(L_FUNCN)
                                      //`--------------------------'  `--------------------------'
  ),

  // Colemak
  [L_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_GESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CW_TOGG, CHOME_A, CHOME_R, CHOME_S, CHOME_T,    KC_G,                         KC_M, CHOME_N, CHOME_E, CHOME_I, CHOME_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
            LT(L_GUI,KC_LGUI), LT(L_NUM,KC_TAB), LT(L_NAVI,KC_SPC),     KC_ENT, MT(MOD_LSFT, KC_BSPC), MO(L_FUNCN)
                                      //`--------------------------'  `--------------------------'
  ),

  [L_GAME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,   KC_J,     KC_K,    KC_L,KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LGUI, KC_LALT, KC_SPC,    KC_ENT, KC_RALT, MO(L_FUNCN)
                                      //`--------------------------'  `--------------------------'
  ),

  [L_GAME1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_ESCAPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,                         KC_0,    KC_5,    KC_6,    KC_7, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX, KC_UP,       KC_ENT, XXXXXXX, MO(L_FUNCN) 
                                      //`--------------------------'  `--------------------------'
  ),

  [L_GAME2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_ESCAPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    KC_E,    KC_R,    KC_T, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX,    KC_Z,   KC_X,    KC_C, XXXXXXX, XXXXXXX,                         KC_Q,    KC_G,KC_LBRC,KC_RBRC, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_F, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX, KC_V,       KC_ENT, XXXXXXX, MO(L_FUNCN) 
                                      //`--------------------------'  `--------------------------'
  ),

  [L_NAVI] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, _______, _______, _______, _______, _______,                      _______, KC_PGUP,  PRVTAB, NXTTAB, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, KC_PGDN, KC_WH_U, _______,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, KC_WH_D, _______,                      _______, _______, KC_WBAK, KC_WFWD, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,   KC_9,   KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,   _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

//   [L_NUM] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//    S(KC_GRV), KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LSFT, XXXXXXX, KC_MINS,S(KC_MINS),KC_EQL, S(KC_EQL),                   KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), KC_BSLS, S(KC_BSLS),
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                           _______, _______,  KC_SPC,    KC_BSLS, _______, S(KC_BSLS)
//                                       //`--------------------------'  `--------------------------'
//   ),

// Symbol layer
  [L_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,KC_GRAVE,   KC_LT,   KC_GT, KC_HASH, KC_PERC,                      _______, KC_AMPR,S(KC_LBRC),S(KC_RBRC),_______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM, KC_MINS, KC_PLUS,KC_EQUAL,  KC_DLR,                      KC_CIRC, KC_PIPE,  KC_LPRN, KC_RPRN, KC_COLN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,   KC_AT, KC_SLSH, KC_ASTR, KC_BSLS,  BACK_D,                      _______, KC_TILD,  KC_LBRC, KC_RBRC, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, KC_UNDS, _______,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_GUI] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, _______, _______, _______, _______, _______,                      _______,  DESK_UP, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______,DESK_DOWN,_______, _______,                    WIN_LEFT, WIN_DOWN, WIN_UP,WIN_RIGHT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______, _______,     _______, KC_LSFT, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [L_FUNCN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______,  KC_F11,  KC_F12, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                            DF(L_GAME), DF(L_QWERTY), DF(L_COLEMAK),     DF(L_GAME1), DF(L_GAME2), _______
                                      //`--------------------------'  `--------------------------'
  ),



//// Empty layer template
//   [LAYER_NAME] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                          _______, _______, _______,     _______, _______, _______
//                                       //`--------------------------'  `--------------------------'
//   ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }

    switch (keycode) {
    case BACK_D:
        if (record->event.pressed) {
            SEND_STRING("../");
        }
    }
    return true;
}
