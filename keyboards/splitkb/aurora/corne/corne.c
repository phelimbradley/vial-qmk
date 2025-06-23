/* Copyright 2022 splitkb.com <support@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// The layers get a name for readability, which is then used in the OLED below.
enum layers {
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

#ifdef OLED_ENABLE
// NOTE: Most of the OLED code was originally written by Soundmonster for the Corne,
// and has been copied directly from `crkbd/soundmonster/keymap.c`

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

static void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

static void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

static void render_logo(void) {
    static const char PROGMEM aurora_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0x60, 0x70, 0x30, 0x38, 0x18, 0x18, 0x18, 0x98, 0xF8,
		0xBC, 0x98, 0x18, 0x18, 0x18, 0x30, 0x30, 0x60, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0xC0, 0xF0, 0x7C, 0x0F, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x81, 0x00,
		0x80, 0xD7, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1E, 0xFC, 0xF0, 0x00,
		0xFF, 0xFF, 0x08, 0x18, 0x10, 0x30, 0x30, 0x20, 0x20, 0x60, 0x40, 0x40, 0x40, 0x40, 0x41, 0x7F,
		0x6B, 0x40, 0x40, 0x40, 0x60, 0x40, 0x60, 0x20, 0x20, 0x30, 0x10, 0x10, 0x18, 0x1D, 0xFF, 0xFE,
		0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
		0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xBF,
		0x01, 0x0F, 0x3E, 0x78, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xF0, 0x3C, 0x1F, 0x07, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x06, 0x0E, 0x0C, 0x0C, 0x0C, 0x18, 0x18, 0x18,
		0x18, 0x18, 0x18, 0x0C, 0x0C, 0x0C, 0x06, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(aurora_logo, sizeof(aurora_logo));
    //oled_set_cursor(0, 4);
}

/*
static void render_logo(void) {
    static const char PROGMEM aurora_logo[] = {
        0x00, 0x00, 0x00, 0xe0, 0x00, 0xf8, 0xc0, 0xf8, 0xe0, 0xc0, 0xfc, 0x00, 0x7e, 0x18, 0x00, 0x80, 
        0x00, 0x02, 0x80, 0xf0, 0x00, 0xc0, 0x80, 0xf8, 0xc0, 0xe0, 0x70, 0x60, 0x3c, 0x38, 0x3c, 0x1c, 
        0x00, 0x3f, 0x0c, 0x0f, 0x1f, 0x03, 0x07, 0x01, 0xc3, 0x00, 0xe0, 0x80, 0x00, 0xe0, 0x80, 0xf8, 
        0x80, 0xc0, 0xf7, 0xc7, 0x6f, 0x7b, 0x39, 0x30, 0x00, 0x80, 0x00, 0xc0, 0x00, 0xc0, 0xc2, 0xe0, 
        0x00, 0x40, 0x38, 0x30, 0x38, 0x1e, 0x18, 0x1e, 0x0f, 0x0c, 0x07, 0x07, 0x07, 0x03, 0x03, 0x21, 
        0x21, 0x31, 0x30, 0x18, 0x18, 0x1c, 0x08, 0x0c, 0x0e, 0x07, 0x06, 0x07, 0x03, 0xc3, 0x03, 0x01, 
        0x4c, 0xcc, 0xc2, 0xc2, 0x41, 0x49, 0x09, 0x2b, 0x2a, 0x6a, 0x6e, 0x24, 0x24, 0x04, 0x92, 0x92, 
        0xb1, 0xf1, 0xf1, 0xf2, 0xe6, 0xa4, 0xa4, 0x04, 0x04, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28
    };
    oled_write_raw_P(aurora_logo, sizeof(aurora_logo));
    oled_set_cursor(0, 4);
}
*/

static void render_logo_text(void) {
    //oled_write_P(PSTR("Corne"), false);
}

/*
static void render_kb_LED_state(void) {
    // Host Keyboard LED Status
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR("  "), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
    oled_write_P(led_usb_state.scroll_lock ? PSTR("S ") : PSTR("  "), false);
}
*/

static void render_layer_state(void) {

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case HOME:		
			oled_write_P(PSTR("HOME "), false);	
			oled_write_P(PSTR("     "), false);
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}			
            break;
			
        case MOUSE:
			oled_write_P(PSTR("MOUSE"), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				render_logo();
				//oled_write_P(PSTR("0    "), false);
				//oled_write_P(PSTR("1    "), false);
				//oled_write_P(PSTR("2    "), false);
			}
            break;
			
        case MAC_1:
			oled_write_P(PSTR("MAC_1"), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;
			
		case MAC_2:
			oled_write_P(PSTR("MAC_2"), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;	
			
		case SYMB:
			oled_write_P(PSTR("SYMB "), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {			
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;
			
        
			
		case NUMS:
			oled_write_P(PSTR("NUMS "), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()==false){
				oled_write_P(PSTR("*789,"), false);
				oled_write_P(PSTR("+4560"), false);
				oled_write_P(PSTR("-123."), false);
			}
			else {
				oled_write_P(PSTR("BCDEF"), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;	

		case SEVEN:
			oled_write_P(PSTR("SEVEN"), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;					
	

		case EIGHT:
			oled_write_P(PSTR("EIGHT"), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;				
	
		case NINE:
			oled_write_P(PSTR("NINE "), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;			
	
		case TEN:
			oled_write_P(PSTR("TEN  "), false);
			oled_write_P(PSTR("     "), false);
			
			if (is_keyboard_master()){
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
			else {
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
				oled_write_P(PSTR("     "), false);
			}
            break;			
	
        default:
            oled_write_P(PSTR("OTHER"), false);			
    }
}

bool oled_task_kb(void) {
	if (!oled_task_user()) {
		return false;
	}
  //if (is_keyboard_master()==false) {
	//  render_logo();
  //}
  //else {
		// Renders the current keyboard state (layers and mods)
		//render_logo();
		render_logo_text();
		render_space();
		render_layer_state();
		if (is_keyboard_master()) {
			render_space();
			render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
			render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
				render_space();
			if (is_caps_word_on()){
				oled_write_P(PSTR("CWORD"),false);
			}
			else {
				render_space();
			}
			if (host_keyboard_led_state().caps_lock){
				oled_write_P(PSTR("CAPSL"),false);
			}
			else {
				render_space();
			}
		}
	return false;
	  
}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    // 0 is left-half encoder,
    // 1 is right-half encoder
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
#endif
