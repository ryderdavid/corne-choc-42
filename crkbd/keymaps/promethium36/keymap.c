#include QMK_KEYBOARD_H

enum layers {
    _HDP = 0,
    _QWERTY,
    _NAV,
    _SYM,
    _NUM,
    _MOUSE,
};

enum custom_keycodes {
    TG_BASE = SAFE_RANGE,
    KC_NT_APOS,
    KC_WHAT,
    KC_WHEN,
    KC_WHERE,
};

enum tap_dances {
    TD_V_Q = 0,
    TD_W_Z,
    TD_J_LBRC,
    TD_SC_RBRC,
    TD_K_LPRN,
    TD_CM_RPRN,
    TD_X_LCBR,
    TD_MN_RCBR,
    TD_1,
    TD_2,
    TD_3,
    TD_4,
    TD_5,
    TD_6,
    TD_7,
    TD_8,
    TD_9,
    TD_0,
};

#define TH_V_Q   TD(TD_V_Q)
#define TH_W_Z   TD(TD_W_Z)
#define TH_J_LB  TD(TD_J_LBRC)
#define TH_SC_RB TD(TD_SC_RBRC)
#define TH_K_LP  TD(TD_K_LPRN)
#define TH_CM_RP TD(TD_CM_RPRN)
#define TH_X_LC  TD(TD_X_LCBR)
#define TH_MN_RC TD(TD_MN_RCBR)

// Hands Down Promethium home row mods (pinky->index)
#define HDP_S_NAV LT(_NAV, KC_S)
#define HDP_N_CTL MT(MOD_LCTL, KC_N)
#define HDP_T_ALT MT(MOD_LALT, KC_T)
#define HDP_H_GUI MT(MOD_LGUI, KC_H)
#define HDP_A_GUI MT(MOD_RGUI, KC_A)
#define HDP_E_ALT MT(MOD_RALT, KC_E)
#define HDP_I_CTL MT(MOD_RCTL, KC_I)
#define HDP_C_NAV LT(_NAV, KC_C)
#define HDP_F_SFT MT(MOD_LSFT, KC_F)
#define HDP_B_SFT MT(MOD_RSFT, KC_B)

// QWERTY home row mods (pinky->index)
#define QW_A_NAV  LT(_NAV, KC_A)
#define QW_S_CTL  MT(MOD_LCTL, KC_S)
#define QW_D_ALT  MT(MOD_LALT, KC_D)
#define QW_F_GUI  MT(MOD_LGUI, KC_F)
#define QW_J_GUI  MT(MOD_RGUI, KC_J)
#define QW_K_ALT  MT(MOD_RALT, KC_K)
#define QW_L_CTL  MT(MOD_RCTL, KC_L)
#define QW_SC_NAV LT(_NAV, KC_SCLN)
#define QW_Z_SFT  MT(MOD_LSFT, KC_Z)
#define QW_SL_SFT MT(MOD_RSFT, KC_SLSH)

// Natural left-to-right ordering: first block of row args = physical LEFT,
// second block = physical RIGHT. Each half reads outer-pinky -> index across
// its block.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HDP] = LAYOUT_split_3x5_3(
        TH_V_Q,    TH_W_Z,    KC_G,      KC_M,      TH_J_LB,        TH_SC_RB,  KC_DOT,    KC_QUOT,   KC_SLSH,   KC_BSPC,
        HDP_S_NAV, HDP_N_CTL, HDP_T_ALT, HDP_H_GUI, TH_K_LP,        TH_CM_RP,  HDP_A_GUI, HDP_E_ALT, HDP_I_CTL, HDP_C_NAV,
        HDP_F_SFT, KC_P,      KC_D,      KC_L,      TH_X_LC,        TH_MN_RC,  KC_U,      KC_O,      KC_Y,      HDP_B_SFT,
                                KC_LGUI, LT(_NUM, KC_SPC), LT(_MOUSE, KC_R),       KC_SPC, LT(_NUM, KC_SPC), KC_SPC
    ),

    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,             KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
        QW_A_NAV, QW_S_CTL, QW_D_ALT, QW_F_GUI, KC_G,             KC_H,     QW_J_GUI, QW_K_ALT, QW_L_CTL, QW_SC_NAV,
        QW_Z_SFT, KC_X,     KC_C,     KC_V,     KC_B,             KC_N,     KC_M,     KC_COMM,  KC_DOT,   QW_SL_SFT,
                                 KC_LGUI, MO(_NAV), KC_SPC,   KC_SPC, KC_SPC, KC_SPC
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, KC_VOLU,
        XXXXXXX, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,     KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,
                                _______, _______, KC_ENT,    KC_ENT, _______, _______
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
                                _______, _______, _______,   _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        TD(TD_1), TD(TD_2), TD(TD_3), TD(TD_4), TD(TD_5),     XXXXXXX, TD(TD_7), TD(TD_8), TD(TD_9), XXXXXXX,
        TD(TD_6), TD(TD_7), TD(TD_8), TD(TD_9), TD(TD_0),     XXXXXXX, TD(TD_4), TD(TD_5), TD(TD_6), XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,      XXXXXXX, TD(TD_1), TD(TD_2), TD(TD_3), XXXXXXX,
                                _______, _______, _______,    _______, TD(TD_0), KC_DOT
    ),

    [_MOUSE] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, MS_WHLU, MS_UP,   MS_WHLD, XXXXXXX,
        XXXXXXX, MS_ACL0, MS_ACL1, MS_ACL2, XXXXXXX,         XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                _______, _______, _______,       MS_BTN1, MS_BTN2, MS_BTN3
    ),
};

// Layout-switch combo: right bottom row 4 keys (U/O/Y/B on HDP, M/,/./ / on QWERTY)
const uint16_t PROGMEM combo_hdp_toggle[]    = { KC_U, KC_O, KC_Y, HDP_B_SFT, COMBO_END };
const uint16_t PROGMEM combo_qwerty_toggle[] = { KC_M, KC_COMM, KC_DOT, QW_SL_SFT, COMBO_END };
const uint16_t PROGMEM combo_qwerty_bspc[]   = { KC_P, KC_O, COMBO_END };
const uint16_t PROGMEM combo_hdp_esc[]       = { TH_V_Q, TH_W_Z, COMBO_END };
const uint16_t PROGMEM combo_qwerty_esc[]    = { KC_Q, KC_W, COMBO_END };
const uint16_t PROGMEM combo_hdp_tab[]       = { HDP_S_NAV, HDP_N_CTL, COMBO_END };
const uint16_t PROGMEM combo_hdp_nt[]        = { HDP_N_CTL, HDP_T_ALT, COMBO_END };
const uint16_t PROGMEM combo_hdp_what[]      = { TH_W_Z, HDP_H_GUI, HDP_A_GUI, COMBO_END };
const uint16_t PROGMEM combo_hdp_when[]      = { TH_W_Z, HDP_H_GUI, HDP_E_ALT, COMBO_END };
const uint16_t PROGMEM combo_hdp_where[]     = { TH_W_Z, HDP_H_GUI, KC_R,      COMBO_END };
const uint16_t PROGMEM combo_hdp_enter[]     = { KC_Y, HDP_B_SFT, COMBO_END };
const uint16_t PROGMEM combo_hdp_equal[]     = { TH_MN_RC, KC_U, COMBO_END };
const uint16_t PROGMEM combo_hdp_excl[]      = { TH_SC_RB, KC_DOT, COMBO_END };

combo_t key_combos[] = {
    COMBO(combo_hdp_toggle, TG_BASE),
    COMBO(combo_qwerty_toggle, TG_BASE),
    COMBO(combo_qwerty_bspc, KC_BSPC),
    COMBO(combo_hdp_esc, KC_ESC),
    COMBO(combo_qwerty_esc, KC_ESC),
    COMBO(combo_hdp_tab, KC_TAB),
    COMBO(combo_hdp_nt,    KC_NT_APOS),
    COMBO(combo_hdp_what,  KC_WHAT),
    COMBO(combo_hdp_when,  KC_WHEN),
    COMBO(combo_hdp_where, KC_WHERE),
    COMBO(combo_hdp_enter, KC_ENT),
    COMBO(combo_hdp_equal, KC_EQL),
    COMBO(combo_hdp_excl,  KC_EXLM),
};

// Tap dance: tap = first kc, hold = second kc (both are plain letters).
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} td_tap_hold_t;

void td_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    td_tap_hold_t *th = (td_tap_hold_t *)user_data;
    if (state->pressed) {
        if (state->count == 1 && !state->interrupted) {
            register_code16(th->hold);
            th->held = th->hold;
        } else {
            register_code16(th->tap);
            th->held = th->tap;
        }
    } else {
        register_code16(th->tap);
        th->held = th->tap;
    }
}

void td_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    td_tap_hold_t *th = (td_tap_hold_t *)user_data;
    wait_ms(10);
    unregister_code16(th->held);
    th->held = 0;
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap_kc, hold_kc) \
    { .fn = { NULL, td_tap_hold_finished, td_tap_hold_reset }, \
      .user_data = (void *)&((td_tap_hold_t){ tap_kc, hold_kc, 0 }) }

tap_dance_action_t tap_dance_actions[] = {
    [TD_V_Q]     = ACTION_TAP_DANCE_TAP_HOLD(KC_V,    KC_Q),
    [TD_W_Z]     = ACTION_TAP_DANCE_TAP_HOLD(KC_W,    KC_Z),
    [TD_J_LBRC]  = ACTION_TAP_DANCE_TAP_HOLD(KC_J,    KC_LBRC),
    [TD_SC_RBRC] = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, KC_RBRC),
    [TD_K_LPRN]  = ACTION_TAP_DANCE_TAP_HOLD(KC_K,    KC_LPRN),
    [TD_CM_RPRN] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_RPRN),
    [TD_X_LCBR]  = ACTION_TAP_DANCE_TAP_HOLD(KC_X,    KC_LCBR),
    [TD_MN_RCBR] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_RCBR),
    [TD_1] = ACTION_TAP_DANCE_TAP_HOLD(KC_1, KC_EXLM),
    [TD_2] = ACTION_TAP_DANCE_TAP_HOLD(KC_2, KC_AT),
    [TD_3] = ACTION_TAP_DANCE_TAP_HOLD(KC_3, KC_HASH),
    [TD_4] = ACTION_TAP_DANCE_TAP_HOLD(KC_4, KC_DLR),
    [TD_5] = ACTION_TAP_DANCE_TAP_HOLD(KC_5, KC_PERC),
    [TD_6] = ACTION_TAP_DANCE_TAP_HOLD(KC_6, KC_CIRC),
    [TD_7] = ACTION_TAP_DANCE_TAP_HOLD(KC_7, KC_AMPR),
    [TD_8] = ACTION_TAP_DANCE_TAP_HOLD(KC_8, KC_ASTR),
    [TD_9] = ACTION_TAP_DANCE_TAP_HOLD(KC_9, KC_LPRN),
    [TD_0] = ACTION_TAP_DANCE_TAP_HOLD(KC_0, KC_RPRN),
};

// Magic H: last key tracking for HDP contextual completions.
static uint16_t last_tap_kc = KC_NO;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;
    switch (keycode) {
        case TG_BASE: {
            uint8_t current = get_highest_layer(default_layer_state);
            set_single_persistent_default_layer(current == _HDP ? _QWERTY : _HDP);
            return false;
        }
        case KC_NT_APOS: SEND_STRING("n't");   return false;
        case KC_WHAT:    SEND_STRING("what");  return false;
        case KC_WHEN:    SEND_STRING("when");  return false;
        case KC_WHERE:   SEND_STRING("where"); return false;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return;
    if (get_highest_layer(default_layer_state) != _HDP) {
        last_tap_kc = keycode;
        return;
    }

    // i + h -> ing (h already emitted; backspace it, then append "ng")
    if (keycode == HDP_H_GUI && record->tap.count > 0 && last_tap_kc == HDP_I_CTL) {
        SEND_STRING(SS_TAP(X_BSPC) "ng");
        last_tap_kc = KC_NO;
        return;
    }

    // t + n -> tion (n already emitted; backspace it, then append "ion")
    if (keycode == HDP_N_CTL && record->tap.count > 0 && last_tap_kc == HDP_T_ALT) {
        SEND_STRING(SS_TAP(X_BSPC) "ion");
        last_tap_kc = KC_NO;
        return;
    }

    last_tap_kc = keycode;
}

#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

static void oled_render_base(void) {
    oled_write_P(PSTR("Base:  "), false);
    switch (get_highest_layer(default_layer_state)) {
        case _HDP:    oled_write_ln_P(PSTR("HDP"),   false); break;
        case _QWERTY: oled_write_ln_P(PSTR("QWRTY"), false); break;
        default:      oled_write_ln_P(PSTR("?"),     false); break;
    }
}

static void oled_render_layer(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _HDP:
        case _QWERTY: oled_write_ln_P(PSTR("Default"), false); break;
        case _NAV:    oled_write_ln_P(PSTR("Nav"),     false); break;
        case _SYM:    oled_write_ln_P(PSTR("Sym"),     false); break;
        case _NUM:    oled_write_ln_P(PSTR("Num"),     false); break;
        case _MOUSE:  oled_write_ln_P(PSTR("Mouse"),   false); break;
        default:      oled_write_ln_P(PSTR("?"),       false); break;
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_base();
        oled_render_layer();
    }
    return false;
}
#endif
