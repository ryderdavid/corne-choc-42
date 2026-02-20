// Corne Choc 42-Key — QWERTY Layout
// macOS-optimized with SCAG home row mods
//
// Layers:
//   0 = Base (QWERTY)
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
// Left hand
#define HM_A  LSFT_T(KC_A)
#define HM_S  LCTL_T(KC_S)
#define HM_D  LALT_T(KC_D)
#define HM_F  LGUI_T(KC_F)

// Right hand
#define HM_J   RGUI_T(KC_J)
#define HM_K   RALT_T(KC_K)
#define HM_L   RCTL_T(KC_L)
#define HM_SCLN RSFT_T(KC_SCLN)

// Thumb keys
#define LW_SPC LT(_LOWER, KC_SPC)
#define RS_ENT LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Base — QWERTY with SCAG home row mods                               │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ,--------------------------------------------.  ,--------------------------------------------.
    // | Tab  |  Q   |  W   |  E   |  R   |  T     |  |  Y   |  U   |  I   |  O   |  P   | Bspc   |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | Esc  |  A   |  S   |  D   |  F   |  G     |  |  H   |  J   |  K   |  L   |  ;   |  '     |
    // |      | Sft  | Ctl  | Opt  | Cmd  |        |  |      | Cmd  | Opt  | Ctl  | Sft  |        |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | Sft  |  Z   |  X   |  C   |  V   |  B     |  |  N   |  M   |  ,   |  .   |  /   | Sft    |
    // `------+------+------+------+------+---------'  `---------+------+------+------+------+------'
    //                      | Opt  | Cmd  | Lwr/ |      | Rse/ | Cmd  | Opt  |
    //                      |      |      | Spc  |      | Ent  |      |      |
    //                      `--------------------'      `--------------------'

    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  HM_A,    HM_S,    HM_D,    HM_F,    KC_G,         KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                    KC_LALT, KC_LGUI, LW_SPC,       RS_ENT,  KC_RGUI, KC_RALT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Lower — Numbers, F-keys, symbols                                    │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ,--------------------------------------------.  ,--------------------------------------------.
    // |  `   |  1   |  2   |  3   |  4   |  5     |  |  6   |  7   |  8   |  9   |  0   | Del    |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // |  ~   |  !   |  @   |  #   |  $   |  %     |  |  ^   |  &   |  *   |  (   |  )   |  |     |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // |      |  F1  |  F2  |  F3  |  F4  |  F5    |  |  F6  |  F7  |  F8  |  F9  | F10  |        |
    // `------+------+------+------+------+---------'  `---------+------+------+------+------+------'
    //                      |      |      | ▓▓▓▓ |      |  ADJ | F11  | F12  |
    //                      `--------------------'      `--------------------'

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      MO(_ADJUST), KC_F11, KC_F12
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Raise — Navigation, editing, media                                  │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ,--------------------------------------------.  ,--------------------------------------------.
    // |      | Undo | Cut  | Copy | Paste|        |  | PgUp | Home |  Up  | End  |      | Del    |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // |      | Sft  | Ctl  | Opt  | Cmd  |        |  | PgDn | Left | Down | Rght |      |        |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // |      | Vol- | Vol+ | Mute | Play |        |  |      |  -   |  =   |  [   |  ]   |  \     |
    // `------+------+------+------+------+---------'  `---------+------+------+------+------+------'
    //                      |      |      |  ADJ |      | ▓▓▓▓ |      |      |
    //                      `--------------------'      `--------------------'

    [_RAISE] = LAYOUT_split_3x6_3(
        KC_TRNS, G(KC_Z), G(KC_X), G(KC_C), G(KC_V), KC_NO,        KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_DEL,
        KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO,        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO,        KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                                    KC_TRNS, KC_TRNS, MO(_ADJUST),  KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Adjust — System (activated by Lower + Raise)                        │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ,--------------------------------------------.  ,--------------------------------------------.
    // | Boot |      |      |      |      |        |  |      |      |      |      |      | Boot   |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // |      | BRI- | BRI+ |      |      |        |  |      |      |      |      |      |        |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | CWrd |      |      |      |      |        |  |      |      |      |      |      |        |
    // `------+------+------+------+------+---------'  `---------+------+------+------+------+------'
    //                      |      |      |      |      |      |      |      |
    //                      `--------------------'      `--------------------'

    [_ADJUST] = LAYOUT_split_3x6_3(
        QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_BOOT,
        KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        CW_TOGG, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
