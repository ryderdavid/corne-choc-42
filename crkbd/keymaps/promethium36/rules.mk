OLED_ENABLE         = yes
OLED_DRIVER         = ssd1306
COMBO_ENABLE        = yes
MOUSEKEY_ENABLE     = yes
EXTRAKEY_ENABLE     = yes

CAPS_WORD_ENABLE    = yes

RGBLIGHT_ENABLE     = no
RGB_MATRIX_ENABLE   = no

# Load gitignored .env (SECRET_PHRASE=...) and pass to compiler if set.
-include $(dir $(lastword $(MAKEFILE_LIST))).env
ifneq ($(strip $(SECRET_PHRASE)),)
    OPT_DEFS += -DSECRET_PHRASE='"$(SECRET_PHRASE)"'
endif
