ENCODER_MAP_ENABLE = yes

# A default 32u4 build is more than 8k oversized,
# so we have to disable some less-common / expert-level features.

VPATH += keyboards/gboards/

MOUSEKEY_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
SEND_STRING_ENABLE = yes
CAPS_WORD_ENABLE = yes
