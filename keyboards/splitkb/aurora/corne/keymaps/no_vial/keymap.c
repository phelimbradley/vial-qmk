#include QMK_KEYBOARD_H

#include "phelim_custom_corne.h"
#include "g/keymap_combo.h"

// Just some names for the layers
enum {
    DEF,
	MOUSE,
	SYMB,
	MACRO,
	NUM,
};

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LSFT, KC_SPC):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
#endif

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {    
        case MT(MOD_LSFT, KC_SPC):
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}
#endif

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
		case TD(TD_COLONS):
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case CK_CAPSWORD:
            if (record->event.pressed) {
                caps_word_on();
            }
            return false;

        case SS_GIT_STATUS:
            if (record->event.pressed) {
                SEND_STRING("git status" SS_TAP(X_ENTER));
            }
            return false;

        case SS_GIT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push");
            }
            return false;

        case SS_GIT_DIFF:
            if (record->event.pressed) {
                SEND_STRING("git diff");
            }
            return false;

        case SS_GIT_COMMIT:
            if (record->event.pressed) {
                SEND_STRING("git commit -a -m \"\"" SS_TAP(X_LEFT));
            }
            return false;
       
        case SS_PHELIM:
            if (record->event.pressed) {
               SEND_STRING("Phelim ");
            }
            return false;
        case SS_BRADLEY:
            if (record->event.pressed) {
               SEND_STRING("Bradley");
            }
            return false;
        case SS_AE:
            if (record->event.pressed) {
               SEND_STRING("Advanced Energy");
            }
            return false;
        case SS_EMAIL:
            if (record->event.pressed) {
               SEND_STRING("psb_@hotmail.com");
            }
            return false;
        case SS_UINT8:
            if (record->event.pressed) {
               SEND_STRING("uint8_t ");
            }
            return false;
        case SS_UINT16:
            if (record->event.pressed) {
               SEND_STRING("uint16_t ");
            }
            return false;
        case SS_UINT32:
            if (record->event.pressed) {
               SEND_STRING("uint32_t ");
            }
            return false;
        case SS_WHILE:
            if (record->event.pressed) {
               SEND_STRING("while(1){\n ");
            }
            return false;
        case SS_COMMENT:
            if (record->event.pressed) {
               SEND_STRING("// " SS_TAP(X_DOWN) SS_TAP(X_HOME));
            }
            return false;
			
        case HASH_DEFINE:  
            if (record->event.pressed) {
               SEND_STRING("#define ");
            }
            return false;
        case HASH_INCLUDE: 
            if (record->event.pressed) {
               SEND_STRING("#include  ");
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
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
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
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │    LGUI       │               │               │               │               │               │   │      )        │               │               │               │               │               │
// Tap  │    ESC        │      Q        │      W        │      E        │      R        │      T        │   │      Y        │       U       │      I        │      O        │       P       │      P        │
	         KC_ESC,         KC_Q,            KC_W,          KC_E,           KC_R,           KC_T,                KC_Y,          KC_U,           KC_I,           KC_O,           KC_P,          KC_BSPC,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │       :       │               │
// Tap  │    ESC        │      A        │      S        │       D       │      F        │      G        │   │      H        │      J        │      K        │      L        │       ;       │      P        │
		     KC_LSFT,        KC_A,            KC_S,      LT(NUM,KC_D),       KC_F,         TD(TD_FTAB),       TD(TD_BTAB),        KC_J,       TD(TD_QUOTE),  TD(TD_DQUOTE),   TD(TD_COLONS),        KC_RSFT, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │      -        │               │               │               │      \        │    RCTL       │
// Tap  │    ESC        │      Z        │      X        │      C        │      V        │      B        │   │      N        │      M        │      ,        │      .        │      /        │               │		
		     KC_LCTL,        KC_Z,         TD(TD_CUT),     TD(TD_COPY),   TD(TD_PASTE),      KC_B,            TD(TD_MINUS),  LT(MOUSE,KC_M),    KC_COMM,        KC_DOT,       TD(TD_SLASHES),       KC_RCTL,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │CTRL_BACKSPACE │   │               │    {MACRO}    │    LCTL       │
// Tap                                                  │  Maximize     │   Delete      │   BACKSPACE   │   │    SPACE      │               │               │
		                                                     WIN_UP,        KC_DEL,       TD(TD_BSPC),      LT(SYMB,KC_SPC), LT(MACRO,KC_END),   KC_LCTL
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	[MOUSE] = LAYOUT_split_3x6_3(
	    XXXXXXX, MS_ACL0, KC_2, KC_3, KC_4, MS_WHLU,                      KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, 
		XXXXXXX, MS_ACL1, MS_LEFT, MS_UP, MS_RGHT, XXXXXXX,      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX, 
		XXXXXXX, MS_ACL2, XXXXXXX, MS_DOWN, XXXXXXX, MS_WHLD,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
		KC_LGUI, MS_BTN1, KC_SPC,                                  MS_BTN2, XXXXXXX, KC_RALT
	),
	[SYMB] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │               │      |        │      <        │      [        │      {        │     (         │   │      )        │       }       │      ]        │      >        │      %        │               │
	         KC_NO,         KC_PIPE,          KC_LT,          KC_LBRC,        KC_LCBR,        KC_LPRN,            KC_RPRN,        KC_RCBR,        KC_RBRC,        KC_GT,          KC_PERC,        KC_NO,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │    LSFT       │               │               │       _       │       #       │      ?        │   │       !       │     LEFT      │     UP        │    RIGHT      │               │               │
		     KC_LSFT,        KC_NO,           KC_NO,          KC_UNDS,        KC_HASH,       KC_QUES,           KC_EXLM,        KC_LEFT,        KC_UP,         KC_RIGHT,         KC_NO,          KC_NO, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │    LCTL       │       *       │       $       │      ^        │      ~        │      &        │   │      @        │               │     DOWN      │      /        │      \        │               │		
		     KC_LCTL,        KC_ASTR,       KC_DLR,        KC_CIRC,       KC_TILD,          KC_AMPR,            KC_AT,          KC_NO,          KC_DOWN,         KC_SLSH,        KC_BSLS,        KC_NO,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │               │   │               │               │               │
// Tap                                                  │               │               │               │   │               │               │               │
		                                                     KC_NO,         KC_NO,           KC_NO,              KC_NO,          KC_NO,         KC_NO
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	),
	[MACRO] = LAYOUT_split_3x6_3(KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, 
		KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV, 
		KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, 
		KC_LGUI, MO(3), KC_SPC, KC_ENT, _______, KC_RALT
	),
	[NUM] = LAYOUT_split_3x6_3(
//      ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
// Hold │               │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │      A        │      B        │     C         │      D        │     E         │       F       │   │               │      7        │      8        │      9        │       P       │      P        │
	         KC_A,           KC_B,          KC_C,             KC_D,          KC_E,            KC_F,              KC_NO,          KC_7,           KC_8,           KC_9,           KC_0,          KC_BSPC,    
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │    ESC        │               │               │               │               │               │   │      +        │      4        │      5        │      6        │       ,       │      =        │
		     KC_LSFT,        KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,              KC_PLUS,        KC_4,           KC_5,           KC_6,          KC_COMM,        KC_EQL, 
//	    ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤ 
// Hold │    LGUI       │               │               │               │               │               │   │               │               │               │               │               │               │
// Tap  │    ESC        │               │      X        │      C        │      V        │               │   │      -        │      1        │      2        │      3        │      .        │    ENTER      │		
		     KC_LCTL,        KC_NO,        TD(TD_CUT),     TD(TD_COPY),   TD(TD_PASTE),      KC_NO,               KC_MINS,        KC_1,           KC_2,           KC_3,           KC_DOT,      KC_ENTER,
//      ╰───────────────────────────────────────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────┼───────────────┼───────────────┼───────────────────────────────────────────────╯
// Hold                                                 │               │               │               │   │               │               │               │
// Tap                                                  │               │               │               │   │    SPACE      │  BACKSPACE    │ {TOG LAYER}   │
		                                                     KC_NO,          KC_NO,          KC_NO,          LT(SYMB,KC_SPC),   TD(TD_BSPC),   TG(NUM)
//                                                      ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
	)
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
	[0] = {ENCODER_CCW_CW(WIN_LEFT, WIN_RIGHT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
	[1] = {ENCODER_CCW_CW(WIN_LEFT, WIN_RIGHT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
	[2] = {ENCODER_CCW_CW(WIN_LEFT, WIN_RIGHT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
	[3] = {ENCODER_CCW_CW(WIN_LEFT, WIN_RIGHT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
	[4] = {ENCODER_CCW_CW(WIN_LEFT, WIN_RIGHT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN)}
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



