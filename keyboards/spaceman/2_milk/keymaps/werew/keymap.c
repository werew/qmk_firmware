#include QMK_KEYBOARD_H

#include <stdlib.h>



bool jiggling = false;
uint16_t last_keycode = 0;
deferred_token token;



enum my_keycodes {
    MOUSE_JIG_TOG = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
          MOUSE_JIG_TOG,
          QK_BOOT
    )
};

uint16_t get_rand_code(void);
uint16_t get_rand_code(void){
    switch(rand() % 8){
        case 0:
            return KC_MS_UP;
        case 1:
            return KC_MS_DOWN;
        case 2:
            return KC_MS_LEFT;
        case 3:
            return KC_MS_RIGHT;
        case 4:
            return KC_MS_WH_UP;
        case 5:
            return KC_MS_WH_DOWN;
        case 6:
            return KC_MS_WH_LEFT;
        case 7:
            return KC_MS_WH_RIGHT;
        default:
            return KC_MS_RIGHT;
    }
}

uint32_t jiggling_callback(uint32_t trigger_time, void *cb_arg) {
    if (jiggling){
        //tap_code_delay(KC_MS_UP,3000);
        if (last_keycode == 0){
            //SEND_STRING("on ");
            last_keycode = get_rand_code();
            register_code(last_keycode);
            return 20 + (rand() % 1500);
        }

        //SEND_STRING("off ");
        unregister_code(last_keycode);
        last_keycode = 0;
        return 500 + (rand() % 10000);
    }
    return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MOUSE_JIG_TOG:
      if (record->event.pressed) {
        // Do something when pressed
        jiggling = !jiggling;
        if (jiggling){
            token = defer_exec(1500, jiggling_callback, NULL);
        } else {
            cancel_deferred_exec(token);
            if (last_keycode != 0){
                unregister_code(last_keycode);
                last_keycode = 0;
            }
        }
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

