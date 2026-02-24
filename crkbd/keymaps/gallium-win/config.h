// Corne Choc 42-Key — Gallium Windows Profile
// qmk flash -kb crkbd/rev1 -km gallium-win -e CONVERT_TO=rp2040_ce

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define TAPPING_TERM 180
#define QUICK_TAP_TERM 120        // Repeat key on fast double-tap instead of hold
#define PERMISSIVE_HOLD           // Register hold earlier during fast rolls
#define CHORDAL_HOLD              // Same-hand keys = tap, opposite-hand = hold

#ifdef KEYBOARD_crkbd_rev1_legacy
#    undef USE_I2C
#    define USE_SERIAL
#endif

// Combo settings
#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_TERM 80
#define COMBO_STRICT_TIMER

// Anti-mash guard: suppress accidental simultaneous keypresses within this window (ms)
#define MASH_GUARD_TERM 8

// Trackpad support
#define AZOTEQ_IQS5XX_WIDTH_MM  43
#define AZOTEQ_IQS5XX_HEIGHT_MM 30
#define AZOTEQ_IQS5XX_RESOLUTION_X 1400
#define AZOTEQ_IQS5XX_RESOLUTION_Y 1400
#define AZOTEQ_IQS5XX_TAP_ENABLE true
#define AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE true
#define AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE true
#define AZOTEQ_IQS5XX_SWIPE_X_ENABLE false
#define AZOTEQ_IQS5XX_SWIPE_Y_ENABLE false
#define AZOTEQ_IQS5XX_ZOOM_ENABLE   false
#define AZOTEQ_IQS5XX_TAP_TIME 110
#define AZOTEQ_IQS5XX_TAP_DISTANCE 12
#define AZOTEQ_IQS5XX_HOLD_TIME 320
#define AZOTEQ_IQS5XX_TIMEOUT_MS 20
#define AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE 18

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT

#define MASTER_LEFT

#define USE_SERIAL_PD2
#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_LED_COUNT
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_LED_COUNT 54
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT { 27, 27 }
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP  10
#    define RGBLIGHT_SAT_STEP  17
#    define RGBLIGHT_VAL_STEP  17
#endif

// Vertical OLED orientation (5 chars x 16 lines)
#define OLED_ROTATION OLED_ROTATION_270

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont_custom.c"
