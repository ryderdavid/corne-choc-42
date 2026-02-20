// Corne Choc 42-Key — Gallium v1 Layout (columnar stagger)
// macOS-optimized with SCAG home row mods
//
// Gallium v1 alpha layout:
//   b l d c v   j y o u ,
//   n r t s g   p h a e i
//   q x m w z   k f ' / .
//
// Layers:
//   0 = Base (Gallium v1)
//   1 = Lower (numbers, F-keys, symbols)
//   2 = Raise (navigation, editing, media)
//   3 = Adjust (system, activated by Lower+Raise)

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Home row mods — SCAG order (Shift-Ctrl-Alt/Opt-Gui/Cmd)
// Left hand (Gallium home row: N R T S G)
#define HM_N  LSFT_T(KC_N)
#define HM_R  LCTL_T(KC_R)
#define HM_T  LALT_T(KC_T)
#define HM_S  LGUI_T(KC_S)

// Right hand (Gallium home row: P H A E I)
#define HM_P   RGUI_T(KC_P)
#define HM_A   RALT_T(KC_A)
#define HM_E   RCTL_T(KC_E)
#define HM_I   RSFT_T(KC_I)

// Thumb keys
#define LW_SPC LT(_LOWER, KC_SPC)
#define RS_ENT LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Base — Gallium v1 with SCAG home row mods                           │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ,--------------------------------------------.  ,--------------------------------------------.
    // | Tab  |  B   |  L   |  D   |  C   |  V     |  |  J   |  Y   |  O   |  U   |  ,   | Bspc   |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | Esc  |  N   |  R   |  T   |  S   |  G     |  |  P   |  H   |  A   |  E   |  I   |  ;     |
    // |      | Sft  | Ctl  | Opt  | Cmd  |        |  | Cmd  |      | Opt  | Ctl  | Sft  |        |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | Sft  |  Q   |  X   |  M   |  W   |  Z     |  |  K   |  F   |  '   |  /   |  .   | Sft    |
    // `------+------+------+------+------+---------'  `---------+------+------+------+------+------'
    //                      | Opt  | Cmd  | Lwr/ |      | Rse/ | Cmd  | Opt  |
    //                      |      |      | Spc  |      | Ent  |      |      |
    //                      `--------------------'      `--------------------'

    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_B,    KC_L,    KC_D,    KC_C,    KC_V,         KC_J,    KC_Y,    KC_O,    KC_U,    KC_COMM, KC_BSPC,
        KC_ESC,  HM_N,    HM_R,    HM_T,    HM_S,    KC_G,         HM_P,    KC_H,    HM_A,    HM_E,    HM_I,    KC_SCLN,
        KC_LSFT, KC_Q,    KC_X,    KC_M,    KC_W,    KC_Z,         KC_K,    KC_F,    KC_QUOT, KC_SLSH, KC_DOT,  KC_RSFT,
                                    KC_LALT, KC_LGUI, LW_SPC,       RS_ENT,  KC_RGUI, KC_RALT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Lower — Numbers, F-keys, symbols                                    │
    // └──────────────────────────────────────────────────────────────────────┘

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      MO(_ADJUST), KC_F11, KC_F12
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Raise — Navigation, editing, media                                  │
    // └──────────────────────────────────────────────────────────────────────┘

    [_RAISE] = LAYOUT_split_3x6_3(
        KC_TRNS, G(KC_Z), G(KC_X), G(KC_C), G(KC_V), KC_NO,        KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_DEL,
        KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO,        KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                                    KC_TRNS, KC_TRNS, MO(_ADJUST),  KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Adjust — System (activated by Lower + Raise)                        │
    // └──────────────────────────────────────────────────────────────────────┘

    [_ADJUST] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
        KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        CW_TOGG, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
