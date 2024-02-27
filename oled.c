// #ifdef OLED_ENABLE

#include QMK_KEYBOARD_H
#include "oled.h"
#include "./keymaps/wasabi-neko/takodachi32-animation/tako32-oled.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//   if (!is_keyboard_master()) {
    // return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
//   }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    
    char layer_str[10] = {0};
    snprintf(layer_str, 10, "%08x, %u, %u", layer_state, oled_max_chars(), oled_max_lines());
    // oled_write_ln_P(PSTR(layer_str), false);
    oled_write(layer_str, false);

    // switch (layer_state) {
    //     case L_BASE:
    //         oled_write_ln_P(PSTR("Default"), false);
    //         break;
    //     case L_LOWER:
    //         oled_write_ln_P(PSTR("Lower"), false);
    //         break;
    //     case L_RAISE:
    //         oled_write_ln_P(PSTR("Raise"), false);
    //         break;
    //     case L_ADJUST:
    //     case L_ADJUST|L_LOWER:
    //     case L_ADJUST|L_RAISE:
    //     case L_ADJUST|L_LOWER|L_RAISE:
    //         oled_write_ln_P(PSTR("Adjust"), false);
    //         break;
    // }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};


void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}


void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_tako();
    }
    return false;
}



// #endif // OLED_ENABLE