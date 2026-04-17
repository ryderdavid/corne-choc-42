#include QMK_KEYBOARD_H

#ifndef SECRET_PHRASE
#define SECRET_PHRASE ""
#endif

enum layers {
    _HDP = 0,
    _QWERTY,
    _NAV,
    _SYM,
    _NUM,
    _MOUSE,
    _FKEYS,
};

enum custom_keycodes {
    TG_BASE = SAFE_RANGE,
    KC_NT_APOS,
    KC_WHAT,
    KC_WHEN,
    KC_WHERE,
    KC_TH,
    KC_TS_APOS,
    KC_WH,
    KC_GH,
    KC_PH,
    KC_SH,
    KC_ARROW,
    KC_THEY,
    KC_CK,
    KC_CH,
    MY_UNDO,
    MY_CUT,
    MY_COPY,
    MY_PASTE,
    MY_SELALL,
    TG_WIN,
    KC_SECRET,
    // Linger tap-holds (tap = first kc, hold = second kc). Release-fires semantics:
    // on release within TAPPING_TERM -> tap; on release after -> hold. No wait after release.
    LTH_G_Q,
    LTH_M_Z,
    LTH_K_LB,
    LTH_SC_RB,
    LTH_B_LP,
    LTH_CM_RP,
    LTH_MN_RC,
    LTH_V_LC,
    LTH_1,
    LTH_2,
    LTH_3,
    LTH_4,
    LTH_5,
    LTH_6,
    LTH_7,
    LTH_8,
    LTH_9,
    LTH_0,
    LTH_END,
};

#define LTH_FIRST LTH_G_Q
#define LTH_COUNT (LTH_END - LTH_FIRST)

typedef struct {
    uint16_t tap;
    uint16_t hold;
} lth_t;

static const lth_t lth_table[LTH_COUNT] = {
    [LTH_G_Q    - LTH_FIRST] = { KC_G,    KC_Q    },
    [LTH_M_Z    - LTH_FIRST] = { KC_M,    KC_Z    },
    [LTH_K_LB   - LTH_FIRST] = { KC_K,    KC_LBRC },
    [LTH_SC_RB  - LTH_FIRST] = { KC_SCLN, KC_RBRC },
    [LTH_B_LP   - LTH_FIRST] = { KC_B,    KC_LPRN },
    [LTH_CM_RP  - LTH_FIRST] = { KC_COMM, KC_RPRN },
    [LTH_MN_RC  - LTH_FIRST] = { KC_MINS, KC_RCBR },
    [LTH_V_LC   - LTH_FIRST] = { KC_V,    KC_LCBR },
    [LTH_1      - LTH_FIRST] = { KC_1,    KC_EXLM },
    [LTH_2      - LTH_FIRST] = { KC_2,    KC_AT   },
    [LTH_3      - LTH_FIRST] = { KC_3,    KC_HASH },
    [LTH_4      - LTH_FIRST] = { KC_4,    KC_DLR  },
    [LTH_5      - LTH_FIRST] = { KC_5,    KC_PERC },
    [LTH_6      - LTH_FIRST] = { KC_6,    KC_CIRC },
    [LTH_7      - LTH_FIRST] = { KC_7,    KC_AMPR },
    [LTH_8      - LTH_FIRST] = { KC_8,    KC_ASTR },
    [LTH_9      - LTH_FIRST] = { KC_9,    KC_LPRN },
    [LTH_0      - LTH_FIRST] = { KC_0,    KC_RPRN },
};

static uint16_t lth_press_time[LTH_COUNT] = {0};

// Windows-mode flag. When true, NAV-layer shortcuts (undo/cut/copy/paste/select-all)
// use Ctrl instead of Cmd. Toggled via the I+X combo on HDP.
static bool win_mode = false;

// Hands Down Promethium home row mods (pinky->index): F S N T (H moved to top-left)
#define HDP_F_NAV LT(_NAV, KC_F)
#define HDP_S_CTL MT(MOD_LCTL, KC_S)
#define HDP_N_ALT MT(MOD_LALT, KC_N)
#define HDP_T_GUI MT(MOD_LGUI, KC_T)
#define HDP_A_GUI MT(MOD_RGUI, KC_A)
#define HDP_E_ALT MT(MOD_RALT, KC_E)
#define HDP_I_CTL MT(MOD_RCTL, KC_I)
#define HDP_X_NAV LT(_NAV, KC_X)
#define HDP_P_SFT MT(MOD_LSFT, KC_P)
#define HDP_J_SFT MT(MOD_RSFT, KC_J)

// Num-layer activators on top-left H and top-right BSPC
#define H_NUM    LT(_NUM, KC_H)
#define BSPC_NUM LT(_NUM, KC_BSPC)

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HDP] = LAYOUT_split_3x5_3(
        H_NUM,     KC_W,      LTH_M_Z,   LTH_G_Q,   LTH_K_LB,       LTH_SC_RB, KC_DOT,    KC_QUOT,   KC_SLSH,   BSPC_NUM,
        HDP_F_NAV, HDP_S_CTL, HDP_N_ALT, HDP_T_GUI, LTH_B_LP,        LTH_CM_RP, HDP_A_GUI, HDP_E_ALT, HDP_I_CTL, HDP_X_NAV,
        HDP_P_SFT, KC_C,      KC_L,      KC_D,      LTH_V_LC,        LTH_MN_RC, KC_U,      KC_O,      KC_Y,      HDP_J_SFT,
                                KC_LGUI, LT(_NUM, KC_SPC), LT(_MOUSE, KC_R),       LT(_NAV, KC_SPC), LT(_NUM, KC_SPC), KC_SPC
    ),

    [_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,             KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
        QW_A_NAV, QW_S_CTL, QW_D_ALT, QW_F_GUI, KC_G,             KC_H,     QW_J_GUI, QW_K_ALT, QW_L_CTL, QW_SC_NAV,
        QW_Z_SFT, KC_X,     KC_C,     KC_V,     KC_B,             KC_N,     KC_M,     KC_COMM,  KC_DOT,   QW_SL_SFT,
                                 KC_LGUI, MO(_NAV), KC_SPC,   KC_SPC, KC_SPC, KC_SPC
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, KC_DEL,
        MY_SELALL, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,     KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
        MY_UNDO,   MY_CUT,  MY_COPY, MY_PASTE, XXXXXXX,    KC_END,  XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE,
                                _______, _______, KC_ENT,    KC_ENT, _______, _______
    ),

    [_SYM] = LAYOUT_split_3x5_3(
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
                                _______, _______, _______,   _______, _______, _______
    ),

    [_NUM] = LAYOUT_split_3x5_3(
        LTH_1,   LTH_2,   LTH_3,   LTH_4,   LTH_5,         XXXXXXX, LTH_7,   LTH_8,   LTH_9,   XXXXXXX,
        LTH_6,   LTH_7,   LTH_8,   LTH_9,   LTH_0,         XXXXXXX, LTH_4,   LTH_5,   LTH_6,   XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, LTH_1,   LTH_2,   LTH_3,   XXXXXXX,
                                _______, _______, _______,     _______, LTH_0,   KC_DOT
    ),

    [_FKEYS] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_F11,  KC_F12,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                _______, _______, _______,    _______, _______, _______
    ),

    [_MOUSE] = LAYOUT_split_3x5_3(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, MS_WHLU, MS_UP,   MS_WHLD, XXXXXXX,
        XXXXXXX, MS_ACL0, MS_ACL1, MS_ACL2, XXXXXXX,         XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                _______, _______, _______,       MS_BTN1, MS_BTN2, MS_BTN3
    ),
};

// Combos
const uint16_t PROGMEM combo_hdp_toggle[]    = { KC_U, KC_O, KC_Y, HDP_J_SFT, COMBO_END };
const uint16_t PROGMEM combo_qwerty_toggle[] = { KC_M, KC_COMM, KC_DOT, QW_SL_SFT, COMBO_END };
const uint16_t PROGMEM combo_qwerty_bspc[]   = { KC_P, KC_O, COMBO_END };
const uint16_t PROGMEM combo_hdp_esc[]       = { H_NUM, KC_W, COMBO_END };
const uint16_t PROGMEM combo_qwerty_esc[]    = { KC_Q, KC_W, COMBO_END };
const uint16_t PROGMEM combo_hdp_tab[]       = { H_NUM, HDP_S_CTL, COMBO_END };
const uint16_t PROGMEM combo_hdp_nt[]        = { HDP_N_ALT, HDP_T_GUI, COMBO_END };
const uint16_t PROGMEM combo_hdp_nd[]        = { HDP_N_ALT, KC_D, COMBO_END };
const uint16_t PROGMEM combo_hdp_st[]        = { HDP_S_CTL, HDP_T_GUI, COMBO_END };
const uint16_t PROGMEM combo_hdp_wm[]        = { KC_W, LTH_M_Z, COMBO_END };
const uint16_t PROGMEM combo_hdp_mg[]        = { LTH_M_Z, LTH_G_Q, COMBO_END };
const uint16_t PROGMEM combo_hdp_pc[]        = { HDP_P_SFT, KC_C, COMBO_END };
const uint16_t PROGMEM combo_hdp_cl[]        = { KC_C, KC_L, COMBO_END };
const uint16_t PROGMEM combo_hdp_what[]      = { KC_W, H_NUM, HDP_A_GUI, COMBO_END };
const uint16_t PROGMEM combo_hdp_when[]      = { KC_W, H_NUM, HDP_E_ALT, COMBO_END };
const uint16_t PROGMEM combo_hdp_where[]     = { KC_W, H_NUM, KC_R,      COMBO_END };
const uint16_t PROGMEM combo_hdp_enter[]     = { KC_Y, HDP_J_SFT, COMBO_END };
const uint16_t PROGMEM combo_hdp_sn[]        = { HDP_S_CTL, HDP_N_ALT, COMBO_END };
const uint16_t PROGMEM combo_hdp_arrow[]     = { KC_O, LTH_MN_RC, COMBO_END };
const uint16_t PROGMEM combo_hdp_grave[]     = { HDP_A_GUI, LTH_CM_RP, COMBO_END };
const uint16_t PROGMEM combo_hdp_cd[]        = { KC_C, KC_D, COMBO_END };
const uint16_t PROGMEM combo_hdp_ix[]        = { HDP_I_CTL, HDP_X_NAV, COMBO_END };
const uint16_t PROGMEM combo_hdp_secret[]    = { H_NUM, KC_W, LTH_M_Z, LTH_G_Q, COMBO_END };
const uint16_t PROGMEM combo_hdp_thy[]       = { HDP_T_GUI, H_NUM, KC_Y, COMBO_END };
const uint16_t PROGMEM combo_caps_word[]     = { HDP_P_SFT, HDP_J_SFT, COMBO_END };
const uint16_t PROGMEM combo_hdp_fkeys[]     = { KC_SLSH, BSPC_NUM, COMBO_END };
const uint16_t PROGMEM combo_hdp_equal[]     = { LTH_MN_RC, KC_U, COMBO_END };
const uint16_t PROGMEM combo_hdp_excl[]      = { LTH_SC_RB, KC_DOT, COMBO_END };

combo_t key_combos[] = {
    COMBO(combo_hdp_toggle, TG_BASE),
    COMBO(combo_qwerty_toggle, TG_BASE),
    COMBO(combo_qwerty_bspc, KC_BSPC),
    COMBO(combo_hdp_esc, KC_ESC),
    COMBO(combo_qwerty_esc, KC_ESC),
    COMBO(combo_hdp_tab, KC_TAB),
    COMBO(combo_hdp_nt,    KC_TH),
    COMBO(combo_hdp_nd,    KC_NT_APOS),
    COMBO(combo_hdp_st,    KC_TS_APOS),
    COMBO(combo_hdp_wm,    KC_WH),
    COMBO(combo_hdp_mg,    KC_GH),
    COMBO(combo_hdp_pc,    KC_PH),
    COMBO(combo_hdp_cl,    KC_CH),
    COMBO(combo_hdp_what,  KC_WHAT),
    COMBO(combo_hdp_when,  KC_WHEN),
    COMBO(combo_hdp_where, KC_WHERE),
    COMBO(combo_hdp_enter, TG_WIN),
    COMBO(combo_hdp_sn,    KC_SH),
    COMBO(combo_hdp_arrow, KC_ARROW),
    COMBO(combo_hdp_grave, KC_GRV),
    COMBO(combo_hdp_cd,    KC_CK),
    COMBO(combo_hdp_ix,    KC_ENT),
    COMBO(combo_hdp_secret, KC_SECRET),
    COMBO(combo_hdp_thy,    KC_THEY),
    COMBO(combo_caps_word,  CW_TOGG),
    COMBO(combo_hdp_fkeys,  MO(_FKEYS)),
    COMBO(combo_hdp_equal, KC_EQL),
    COMBO(combo_hdp_excl,  KC_EXLM),
};

// Title-case-aware combo string sender. If shift is held when the combo fires,
// the first char goes uppercase and the rest lowercase.
static void send_combo_string(const char *str) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    if (mods & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        del_oneshot_mods(MOD_MASK_SHIFT);
        send_keyboard_report();
        set_mods(MOD_BIT(KC_LSFT));
        send_keyboard_report();
        char first[2] = { str[0], '\0' };
        send_string(first);
        del_mods(MOD_MASK_SHIFT);
        send_keyboard_report();
        send_string(str + 1);
        set_mods(mods);
        send_keyboard_report();
    } else {
        send_string(str);
    }
}

// Magic H: last key tracking for HDP contextual completions.
static uint16_t last_tap_kc = KC_NO;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Custom linger tap-hold: tap on release < TAPPING_TERM, hold otherwise.
    if (keycode >= LTH_FIRST && keycode < LTH_END) {
        uint8_t idx = keycode - LTH_FIRST;
        if (record->event.pressed) {
            lth_press_time[idx] = record->event.time;
        } else {
            uint16_t elapsed = record->event.time - lth_press_time[idx];
            uint16_t tap_kc  = lth_table[idx].tap;
            uint16_t hold_kc = lth_table[idx].hold;
            lth_press_time[idx] = 0;

            if (elapsed >= TAPPING_TERM) {
                tap_code16(hold_kc);
                last_tap_kc = KC_NO;
                return false;
            }
            tap_code16(tap_kc);
            last_tap_kc = tap_kc;
        }
        return false;
    }

    if (!record->event.pressed) return true;
    switch (keycode) {
        case TG_BASE: {
            uint8_t current = get_highest_layer(default_layer_state);
            set_single_persistent_default_layer(current == _HDP ? _QWERTY : _HDP);
            return false;
        }
        case KC_NT_APOS: send_combo_string("n't");   return false;
        case KC_WHAT:    send_combo_string("what");  return false;
        case KC_WHEN:    send_combo_string("when");  return false;
        case KC_WHERE:   send_combo_string("where"); return false;
        case KC_TH:      send_combo_string("th");    return false;
        case KC_TS_APOS: send_combo_string("t's");   return false;
        case KC_WH:      send_combo_string("wh");    return false;
        case KC_GH:      send_combo_string("gh");    return false;
        case KC_PH:      send_combo_string("ph");    return false;
        case KC_SH:      send_combo_string("sh");    return false;
        case KC_ARROW:   SEND_STRING("->");    return false;
        case KC_THEY:    send_combo_string("they"); return false;
        case KC_CK:      send_combo_string("ck");    return false;
        case KC_CH:      send_combo_string("ch");    return false;
        case TG_WIN:     win_mode = !win_mode; return false;
        case MY_UNDO:    SEND_STRING(win_mode ? SS_LCTL("z") : SS_LGUI("z")); return false;
        case MY_CUT:     SEND_STRING(win_mode ? SS_LCTL("x") : SS_LGUI("x")); return false;
        case MY_COPY:    SEND_STRING(win_mode ? SS_LCTL("c") : SS_LGUI("c")); return false;
        case MY_PASTE:   SEND_STRING(win_mode ? SS_LCTL("v") : SS_LGUI("v")); return false;
        case MY_SELALL:  SEND_STRING(win_mode ? SS_LCTL("a") : SS_LGUI("a")); return false;
        case KC_SECRET:  SEND_STRING(SECRET_PHRASE); return false;
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
    if (keycode == H_NUM && record->tap.count > 0 && last_tap_kc == HDP_I_CTL) {
        SEND_STRING(SS_TAP(X_BSPC) "ng");
        last_tap_kc = KC_NO;
        return;
    }

    // t + n -> tion (n already emitted; backspace it, then append "ion")
    if (keycode == HDP_N_ALT && record->tap.count > 0 && last_tap_kc == HDP_T_GUI) {
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
        case _FKEYS:  oled_write_ln_P(PSTR("FKeys"),   false); break;
        default:      oled_write_ln_P(PSTR("?"),       false); break;
    }
}

static void oled_render_os(void) {
    oled_write_P(PSTR("OS:    "), false);
    oled_write_ln_P(win_mode ? PSTR("WIN") : PSTR("MAC"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_base();
        oled_render_layer();
        oled_render_os();
    }
    return false;
}
#endif
