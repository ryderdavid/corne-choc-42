#pragma once

#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

#define MASTER_LEFT
#define USE_SERIAL_PD2

#define TAPPING_TERM 180
#define QUICK_TAP_TERM 120
#define PERMISSIVE_HOLD
#define CHORDAL_HOLD

#define COMBO_TERM 50

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
