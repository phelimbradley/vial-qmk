#include "sendstring_uk.h"

// Tap Dance declarations

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

#define PB_DESKTOP_LEFT LCTL(LGUI(KC_LEFT))
#define PB_DESKTOP_RIGHT LCTL(LGUI(KC_RIGHT))
#define WIN_RIGHT LGUI(KC_RIGHT)
#define WIN_LEFT LGUI(KC_LEFT)
#define WIN_UP LGUI(KC_UP)
#define DESKTOP_1 LGUI(KC_1)
#define DESKTOP_2 LGUI(KC_2)
#define DESKTOP_3 LGUI(KC_3)
#define DESKTOP_4 LGUI(KC_4)
#define DESKTOP_5 LGUI(KC_5)
#define DESKTOP_6 LGUI(KC_6)
#define SNIP_TOOL LSFT(LGUI(KC_S))


#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// Enum for sendstrings
enum custom_keycodes {
  HASH_DEFINE = SAFE_RANGE,
  HASH_INCLUDE,
  SS_COMMENT,
  SS_UINT8,
  SS_UINT16,
  SS_UINT32,
  SS_WHILE,
  SS_EMAIL,
  SS_AE,
  SS_PHELIM,
  SS_BRADLEY,
  SS_GIT_COMMIT,
  SS_GIT_PUSH,
  SS_GIT_DIFF,
  SS_GIT_STATUS,
  CK_CAPSWORD,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

enum {
    TD_COPY,    // Hold C to copy
    TD_PASTE,   // Hold V to paste
    TD_CUT,     // Hold X to cut
    TD_BSPC,    // Insert CTRL-BACKSPACE when the BACKSPACE is held to perform word deletion         
    TD_FTAB,    // Insert a normal tab when G is held 
    TD_BTAB,    // Insert a shift tab when H is held 
    TD_MINUS,       // Hold N for Minus symbol
    TD_UPARR,       // Hold K for UP
    TD_DOWNARR,       // Hold COMMA for DOWN
    TD_LEFTARR,       // Hold J for LEFT
    TD_RIGHTARR,       // Hold L for RIGHT
	TD_COLONS,		// Holds semicolon for colon
	TD_SLASHES,		// Hold forward slash for backslash
	TD_QUOTE,		// Hold K for single quote
	TD_DQUOTE, 		// Hold L for double quote
}; 

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_COPY] = ACTION_TAP_DANCE_TAP_HOLD(KC_C, LCTL(KC_C)),
    [TD_PASTE] = ACTION_TAP_DANCE_TAP_HOLD(KC_V, LCTL(KC_V)),
    [TD_CUT] = ACTION_TAP_DANCE_TAP_HOLD(KC_X, LCTL(KC_X)),
    [TD_BSPC] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, LCTL(KC_BSPC)),
    [TD_FTAB] = ACTION_TAP_DANCE_TAP_HOLD(KC_G, KC_TAB),
    [TD_BTAB] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, LSFT(KC_TAB)),
    [TD_MINUS] = ACTION_TAP_DANCE_TAP_HOLD(KC_N, KC_MINS),
    [TD_UPARR] = ACTION_TAP_DANCE_TAP_HOLD(KC_K, KC_UP),
    [TD_DOWNARR] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_DOWN),
    [TD_LEFTARR] = ACTION_TAP_DANCE_TAP_HOLD(KC_J, KC_LEFT),
    [TD_RIGHTARR] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_RIGHT),
	[TD_COLONS] = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, LSFT(KC_SCLN)),
	[TD_SLASHES] = ACTION_TAP_DANCE_TAP_HOLD(KC_SLSH, KC_BSLS),
	[TD_QUOTE] = ACTION_TAP_DANCE_TAP_HOLD(KC_K, KC_QUOT),
	[TD_DQUOTE] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_DQUO),
};
