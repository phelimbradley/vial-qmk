#include QMK_KEYBOARD_H

//#include "phelim_custom_corne.h"
//  #include "g/keymap_combo.h"

// Just some names for the layers
enum {
    HOME,
	SYMB,
	NUMS,
	MOUSE,
	MAC_1,
	MAC_2,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that exit Caps Word
        case KC_SPC:
        case KC_ENT:
			unregister_mods(MOD_BIT(KC_LSFT));
            return false;
		
	  
        // Keycodes that continue Caps Word, without shifting.
        case KC_0:
		case KC_1:
		case KC_2:
		case KC_3:
		case KC_4:
		case KC_5:
		case KC_6:
		case KC_7:
		case KC_8:
		case KC_9:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_NUHS:
		case KC_PLUS:
        case KC_ASTR:
        case KC_MINS:
		case KC_COMM:
		case KC_DOT:
		case KC_SLSH:
            return true;

        // For all other non-standard Keycodes, we will keep Caps Word on with shift applied
        default:
			register_mods(MOD_BIT(KC_LSFT));
            //add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true; 
    }
}

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case CK_CAPSWORD:
            if (record->event.pressed) {
                caps_word_on();
            }
            return false;

                    
        // list all tap dance keycodes with tap-hold configurations
		case TD(TD_COPY):  
		case TD(TD_PASTE):
		case TD(TD_CUT):
		case TD(TD_BSPC):
		case TD(TD_FTAB):
		case TD(TD_BTAB):     
		case TD(TD_MINUS):			
        case TD(TD_UPARR):
        case TD(TD_DOWNARR):
        case TD(TD_LEFTARR):
        case TD(TD_RIGHTARR):     
		case TD(TD_COLONS):   
		case TD(TD_SLASHES):
		case TD(TD_QUOTE):		
		case TD(TD_DQUOTE): 	
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    } 
    return true;
}*/

/* void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
} */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[HOME] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         KC_ESC,         KC_Q,            KC_W,          KC_E,           KC_R,           KC_T,                KC_Y,          KC_U,           KC_I,           KC_O,           KC_P,          KC_UP,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     KC_LSFT,        KC_A,            KC_S,           KC_D,           KC_F,         KC_G,                KC_H,        KC_J,                KC_K,          KC_L,           KC_COLN,        KC_RSFT, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     KC_LCTL,        KC_Z,         KC_X,        KC_C,           KC_V,          KC_B,                      KC_N,            KC_M,          KC_COMM,        KC_DOT,       KC_SLSH,       KC_RCTL,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     KC_DEL,        KC_BSPC,       KC_BSPC,            KC_SPC,            KC_SPC,       KC_ENTER
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[SYMB] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[NUMS] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[MOUSE] = LAYOUT_split_3x6_3(
	  //      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	
	[MAC_1] = LAYOUT_split_3x6_3(
	//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[MAC_2] = LAYOUT_split_3x6_3(
	//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[SEVEN] = LAYOUT_split_3x6_3(
	//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[EIGHT] = LAYOUT_split_3x6_3(
	//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[NINE] = LAYOUT_split_3x6_3(
	//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	
	[TEN] = LAYOUT_split_3x6_3(
	//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         XXXXXXX,         XXXXXXX,     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     XXXXXXX,        XXXXXXX,       XXXXXXX,        XXXXXXX,         XXXXXXX,      XXXXXXX,              XXXXXXX,        XXXXXXX,       XXXXXXX,         XXXXXXX,        XXXXXXX,        XXXXXXX, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,      XXXXXXX,               XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,       XXXXXXX,       XXXXXXX,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     XXXXXXX,        XXXXXXX,       XXXXXXX,             XXXXXXX,        XXXXXXX,       XXXXXXX
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	[0] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[1] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[2] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[3] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[4] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[5] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[6] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[7] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[8] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)},
	[9] = {ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(XXXXXXX, XXXXXXX)}
};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

/*
[TEMPLATE] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │               │               │               │               │               │               │   │               │               │               │               │               │               │
	         KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,              KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │               │               │               │               │               │               │   │               │               │               │               │               │               │
		     KC_NO,          KC_NO           KC_NO,          KC_NO,          KC_NO,          KC_NO,              KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │               │               │               │               │               │               │   │               │               │               │               │               │               │		
		     KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,              KC_N0,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │               │   │               │               │               │
// Tap                                                  │               │               │               │   │               │               │               │
		                                                     KC_NO,          KC_NO,          KC_NO,              KC_NO,          KC_NO,          KC_NO
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
    )
};
*/



