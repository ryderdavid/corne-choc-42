// Corne Choc 42-Key — Combined Profile (QWERTY + Gallium × macOS + Windows)
// All 4 layouts in one firmware, cycle with bottom-right 4-key combo
//
// Layers:
//   0 = QWERTY (macOS, SCAG home row mods)
//   1 = Gallium v1 (macOS, SCAG home row mods)
//   2 = QWERTY Windows (SGAC home row mods)
//   3 = Gallium v1 Windows (SGAC home row mods)
//   4 = Numbers
//   5 = Nav
//   6 = Symbols
//   7 = F-Keys

#include QMK_KEYBOARD_H
#include <stdio.h>

// ─── Layer Names ────────────────────────────────────────────────────────────

enum layers {
    _QWERTY,
    _GALLIUM,
    _QWERTY_WIN,
    _GALLIUM_WIN,
    _NUMBERS,
    _NAV,
    _SYMBOLS,
    _FKEYS,
};

// ─── Custom Keycodes ────────────────────────────────────────────────────────

enum custom_keycodes {
    CK_UNDO = SAFE_RANGE,
    CK_CUT,
    CK_COPY,
    CK_PASTE,
};

// ─── QWERTY Home Row Mods — SCAG (macOS) ───────────────────────────────────

#define HM_A    LSFT_T(KC_A)
#define HM_S    LCTL_T(KC_S)
#define HM_D    LALT_T(KC_D)
#define HM_F    LGUI_T(KC_F)

#define HM_J    RGUI_T(KC_J)
#define HM_K    RALT_T(KC_K)
#define HM_L    RCTL_T(KC_L)
#define HM_SCLN RSFT_T(KC_SCLN)

// ─── Gallium Home Row Mods — SCAG (macOS) ───────────────────────────────────

#define GM_N    LSFT_T(KC_N)
#define GM_R    LCTL_T(KC_R)
#define GM_T    LALT_T(KC_T)
#define GM_S    LGUI_T(KC_S)

#define GM_H    RGUI_T(KC_H)
#define GM_A    RALT_T(KC_A)
#define GM_E    RCTL_T(KC_E)
#define GM_I    RSFT_T(KC_I)

// ─── QWERTY Home Row Mods — SGAC (Windows) ─────────────────────────────────

#define WM_A    LSFT_T(KC_A)
#define WM_S    LGUI_T(KC_S)
#define WM_D    LALT_T(KC_D)
#define WM_F    LCTL_T(KC_F)

#define WM_J    RCTL_T(KC_J)
#define WM_K    RALT_T(KC_K)
#define WM_L    RGUI_T(KC_L)
#define WM_SCLN RSFT_T(KC_SCLN)

// ─── Gallium Home Row Mods — SGAC (Windows) ─────────────────────────────────

#define GW_N    LSFT_T(KC_N)
#define GW_R    LGUI_T(KC_R)
#define GW_T    LALT_T(KC_T)
#define GW_S    LCTL_T(KC_S)

#define GW_H    RCTL_T(KC_H)
#define GW_A    RALT_T(KC_A)
#define GW_E    RGUI_T(KC_E)
#define GW_I    RSFT_T(KC_I)

// ─── Thumb Keys ─────────────────────────────────────────────────────────────

#define NAV_SPC LT(_NAV, KC_SPC)
#define SYM_ENT LT(_SYMBOLS, KC_ENT)
#define SYM_SPC LT(_SYMBOLS, KC_SPC)
#define FK_ENT  LT(_FKEYS, KC_ENT)

// ─── Tap Dance ──────────────────────────────────────────────────────────────

enum tap_dances {
    TD_SYM_LAYER,
    TD_SPC_SYM,
    TD_SHIFT_CAPS,
};

#define TD_SYM  TD(TD_SYM_LAYER)
#define TD_SSYM TD(TD_SPC_SYM)
#define TD_SCAP TD(TD_SHIFT_CAPS)

// ─── Combo Definitions ──────────────────────────────────────────────────────

enum combo_events {
    // Utility combos
    CMB_ESC,
    CMB_DEL,
    CMB_BSPC,
    CMB_HYPER_Z,
    CMB_NAV_BACK,     // Y+U = Cmd+[
    CMB_NAV_FWD,      // P+Bksp = Cmd+]
    CMB_CYCLE,        // Bottom-right 4 keys = Cycle layout
    CMB_NUM_TG,

    // QWERTY word chords
    QWC_THE,  QWC_BE,   QWC_TO,   QWC_AND,  QWC_OF,
    QWC_IN,   QWC_HAVE, QWC_THAT, QWC_FOR,  QWC_NOT,
    QWC_WITH, QWC_YOU,  QWC_THIS, QWC_FROM, QWC_BUT,
    QWC_WHAT, QWC_IT,   QWC_HE,   QWC_ON,   QWC_ARE,
    QWC_DO,   QWC_HIS,  QWC_BY,   QWC_THEY, QWC_HER,
    QWC_OR,   QWC_AT,   QWC_ONE,  QWC_HAD,  QWC_SAY,
    QWC_SHE,  QWC_ALL,  QWC_WHICH,QWC_WILL, QWC_WOULD,
    QWC_THERE,QWC_THEIR,QWC_MY,   QWC_OUT,  QWC_UP,
    QWC_ABOUT,QWC_WHO,  QWC_GET,  QWC_MAKE, QWC_GO,
    QWC_LIKE, QWC_JUST, QWC_KNOW, QWC_TAKE, QWC_COME,

    // Gallium word chords
    GWC_THE,  GWC_BE,   GWC_TO,   GWC_AND,  GWC_OF,
    GWC_IN,   GWC_HAVE, GWC_THAT, GWC_FOR,  GWC_NOT,
    GWC_WITH, GWC_YOU,  GWC_THIS, GWC_FROM, GWC_BUT,
    GWC_WHAT, GWC_IT,   GWC_HE,   GWC_ON,   GWC_ARE,
    GWC_DO,   GWC_HIS,  GWC_BY,   GWC_THEY, GWC_HER,
    GWC_OR,   GWC_AT,   GWC_ONE,  GWC_HAD,  GWC_SAY,
    GWC_SHE,  GWC_ALL,  GWC_WHICH,GWC_WILL, GWC_WOULD,
    GWC_THERE,GWC_THEIR,GWC_MY,   GWC_OUT,  GWC_UP,
    GWC_ABOUT,GWC_WHO,  GWC_GET,  GWC_MAKE, GWC_GO,
    GWC_LIKE, GWC_JUST, GWC_KNOW, GWC_TAKE, GWC_COME,

    COMBO_COUNT
};

// Include combo key arrays
#include "combos.def"

// Gate combos by active base layout
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo_index <= CMB_NUM_TG) return true;

    uint8_t base = get_highest_layer(default_layer_state);

    if (combo_index >= QWC_THE && combo_index <= QWC_COME) {
        return (base == _QWERTY || base == _QWERTY_WIN);
    }
    if (combo_index >= GWC_THE && combo_index <= GWC_COME) {
        return (base == _GALLIUM || base == _GALLIUM_WIN);
    }
    return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;
    switch (combo_index) {
        case CMB_CYCLE: {
            uint8_t base = get_highest_layer(default_layer_state);
            uint8_t next;
            switch (base) {
                case _QWERTY:      next = _GALLIUM; break;
                case _GALLIUM:     next = _QWERTY_WIN; break;
                case _QWERTY_WIN:  next = _GALLIUM_WIN; break;
                case _GALLIUM_WIN: next = _QWERTY; break;
                default:           next = _QWERTY; break;
            }
            default_layer_set(1UL << next);
            break;
        }
        case CMB_NAV_BACK: {
            uint8_t base = get_highest_layer(default_layer_state);
            bool win = (base == _QWERTY_WIN || base == _GALLIUM_WIN);
            tap_code16(win ? LCTL(KC_LBRC) : LGUI(KC_LBRC));
            break;
        }
        case CMB_NAV_FWD: {
            uint8_t base = get_highest_layer(default_layer_state);
            bool win = (base == _QWERTY_WIN || base == _GALLIUM_WIN);
            tap_code16(win ? LCTL(KC_RBRC) : LGUI(KC_RBRC));
            break;
        }
        // Word chords (shared between QWERTY and Gallium variants)
        case QWC_THE:   case GWC_THE:   SEND_STRING("the "); break;
        case QWC_BE:    case GWC_BE:    SEND_STRING("be "); break;
        case QWC_TO:    case GWC_TO:    SEND_STRING("to "); break;
        case QWC_AND:   case GWC_AND:   SEND_STRING("and "); break;
        case QWC_OF:    case GWC_OF:    SEND_STRING("of "); break;
        case QWC_IN:    case GWC_IN:    SEND_STRING("in "); break;
        case QWC_HAVE:  case GWC_HAVE:  SEND_STRING("have "); break;
        case QWC_THAT:  case GWC_THAT:  SEND_STRING("that "); break;
        case QWC_FOR:   case GWC_FOR:   SEND_STRING("for "); break;
        case QWC_NOT:   case GWC_NOT:   SEND_STRING("not "); break;
        case QWC_WITH:  case GWC_WITH:  SEND_STRING("with "); break;
        case QWC_YOU:   case GWC_YOU:   SEND_STRING("you "); break;
        case QWC_THIS:  case GWC_THIS:  SEND_STRING("this "); break;
        case QWC_FROM:  case GWC_FROM:  SEND_STRING("from "); break;
        case QWC_BUT:   case GWC_BUT:   SEND_STRING("but "); break;
        case QWC_WHAT:  case GWC_WHAT:  SEND_STRING("what "); break;
        case QWC_IT:    case GWC_IT:    SEND_STRING("it "); break;
        case QWC_HE:    case GWC_HE:    SEND_STRING("he "); break;
        case QWC_ON:    case GWC_ON:    SEND_STRING("on "); break;
        case QWC_ARE:   case GWC_ARE:   SEND_STRING("are "); break;
        case QWC_DO:    case GWC_DO:    SEND_STRING("do "); break;
        case QWC_HIS:   case GWC_HIS:   SEND_STRING("his "); break;
        case QWC_BY:    case GWC_BY:    SEND_STRING("by "); break;
        case QWC_THEY:  case GWC_THEY:  SEND_STRING("they "); break;
        case QWC_HER:   case GWC_HER:   SEND_STRING("her "); break;
        case QWC_OR:    case GWC_OR:    SEND_STRING("or "); break;
        case QWC_AT:    case GWC_AT:    SEND_STRING("at "); break;
        case QWC_ONE:   case GWC_ONE:   SEND_STRING("one "); break;
        case QWC_HAD:   case GWC_HAD:   SEND_STRING("had "); break;
        case QWC_SAY:   case GWC_SAY:   SEND_STRING("say "); break;
        case QWC_SHE:   case GWC_SHE:   SEND_STRING("she "); break;
        case QWC_ALL:   case GWC_ALL:   SEND_STRING("all "); break;
        case QWC_WHICH: case GWC_WHICH: SEND_STRING("which "); break;
        case QWC_WILL:  case GWC_WILL:  SEND_STRING("will "); break;
        case QWC_WOULD: case GWC_WOULD: SEND_STRING("would "); break;
        case QWC_THERE: case GWC_THERE: SEND_STRING("there "); break;
        case QWC_THEIR: case GWC_THEIR: SEND_STRING("their "); break;
        case QWC_MY:    case GWC_MY:    SEND_STRING("my "); break;
        case QWC_OUT:   case GWC_OUT:   SEND_STRING("out "); break;
        case QWC_UP:    case GWC_UP:    SEND_STRING("up "); break;
        case QWC_ABOUT: case GWC_ABOUT: SEND_STRING("about "); break;
        case QWC_WHO:   case GWC_WHO:   SEND_STRING("who "); break;
        case QWC_GET:   case GWC_GET:   SEND_STRING("get "); break;
        case QWC_MAKE:  case GWC_MAKE:  SEND_STRING("make "); break;
        case QWC_GO:    case GWC_GO:    SEND_STRING("go "); break;
        case QWC_LIKE:  case GWC_LIKE:  SEND_STRING("like "); break;
        case QWC_JUST:  case GWC_JUST:  SEND_STRING("just "); break;
        case QWC_KNOW:  case GWC_KNOW:  SEND_STRING("know "); break;
        case QWC_TAKE:  case GWC_TAKE:  SEND_STRING("take "); break;
        case QWC_COME:  case GWC_COME:  SEND_STRING("come "); break;
    }
}

// ─── Keymaps ────────────────────────────────────────────────────────────────

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 0 — QWERTY macOS (SCAG home row mods)                         │
    // └──────────────────────────────────────────────────────────────────────┘

    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_GRV,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        LT(_NAV,KC_TAB), HM_A,    HM_S,    HM_D,    HM_F,    LT(_NUMBERS,KC_G), LT(_NUMBERS,KC_H), HM_J, HM_K, HM_L, HM_SCLN, LT(_SYMBOLS,KC_QUOT),
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_SLSH),
                                       KC_LGUI, NAV_SPC, SYM_ENT,    SYM_SPC, NAV_SPC, FK_ENT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 1 — Gallium v1 macOS (SCAG home row mods)                     │
    // └──────────────────────────────────────────────────────────────────────┘

    [_GALLIUM] = LAYOUT_split_3x6_3(
        KC_GRV,          KC_B,    KC_L,    KC_D,    KC_C,    KC_V,              KC_J,    KC_Y,    KC_O,    KC_U,    KC_MINS, KC_BSPC,
        LT(_NAV,KC_TAB), GM_N,    GM_R,    GM_T,    GM_S,    LT(_NUMBERS,KC_G), LT(_NUMBERS,KC_P), GM_H, GM_A, GM_E, GM_I, LT(_SYMBOLS,KC_SCLN),
        KC_LSFT,          KC_Q,    KC_X,    KC_M,    KC_W,    KC_Z,              KC_K,    KC_F,    KC_COMM, KC_DOT,  KC_QUOT, RSFT_T(KC_SLSH),
                                       KC_LGUI, NAV_SPC, SYM_ENT,    SYM_SPC, NAV_SPC, FK_ENT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 2 — QWERTY Windows (SGAC home row mods)                       │
    // └──────────────────────────────────────────────────────────────────────┘

    [_QWERTY_WIN] = LAYOUT_split_3x6_3(
        KC_GRV,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        LT(_NAV,KC_TAB), WM_A,    WM_S,    WM_D,    WM_F,    LT(_NUMBERS,KC_G), LT(_NUMBERS,KC_H), WM_J, WM_K, WM_L, WM_SCLN, LT(_SYMBOLS,KC_QUOT),
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_SLSH),
                                       KC_LCTL, NAV_SPC, SYM_ENT,    SYM_SPC, NAV_SPC, FK_ENT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 3 — Gallium v1 Windows (SGAC home row mods)                   │
    // └──────────────────────────────────────────────────────────────────────┘

    [_GALLIUM_WIN] = LAYOUT_split_3x6_3(
        KC_GRV,          KC_B,    KC_L,    KC_D,    KC_C,    KC_V,              KC_J,    KC_Y,    KC_O,    KC_U,    KC_MINS, KC_BSPC,
        LT(_NAV,KC_TAB), GW_N,    GW_R,    GW_T,    GW_S,    LT(_NUMBERS,KC_G), LT(_NUMBERS,KC_P), GW_H, GW_A, GW_E, GW_I, LT(_SYMBOLS,KC_SCLN),
        KC_LSFT,          KC_Q,    KC_X,    KC_M,    KC_W,    KC_Z,              KC_K,    KC_F,    KC_COMM, KC_DOT,  KC_QUOT, RSFT_T(KC_SLSH),
                                       KC_LCTL, NAV_SPC, SYM_ENT,    SYM_SPC, NAV_SPC, FK_ENT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 4 — Numbers                                                   │
    // └──────────────────────────────────────────────────────────────────────┘

    [_NUMBERS] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_ASTR, KC_7,    KC_8,    KC_9,    KC_TRNS, KC_BSPC,
        KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,         KC_MINS, KC_4,    KC_5,    KC_6,    KC_TRNS, KC_TRNS,
        KC_TRNS, KC_DOT,  KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS,      KC_PLUS, KC_1,    KC_2,    KC_3,    KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_ENT,  KC_0,    KC_DOT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 5 — Navigation (clipboard adapts to macOS/Windows)             │
    // └──────────────────────────────────────────────────────────────────────┘

    [_NAV] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_NO,   KC_PGUP, KC_UP,   KC_PGDN, G(KC_EQL),  KC_BSPC,
        KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, G(KC_MINS), KC_ENT,
        KC_TRNS, CK_UNDO, CK_CUT,  CK_COPY, CK_PASTE, KC_NO,      KC_END,  MS_WHLD, KC_NO,   MS_WHLU, G(KC_0),    KC_NO,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 6 — Symbols                                                   │
    // └──────────────────────────────────────────────────────────────────────┘

    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_LABK, KC_LCBR, KC_LBRC, KC_LPRN, KC_EQL,  KC_MINS,
        KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,      KC_RABK, KC_RCBR, KC_RBRC, KC_RPRN, KC_PIPE, KC_TRNS,
        KC_TRNS, KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,      KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, KC_BSLS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Layer 7 — F-Keys (held via right outer thumb)                       │
    // └──────────────────────────────────────────────────────────────────────┘

    [_FKEYS] = LAYOUT_split_3x6_3(
        KC_ESC,  G(S(KC_1)), G(S(KC_2)), G(S(KC_3)), G(S(KC_4)), G(S(KC_5)),  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_BSPC,
        KC_TRNS, G(S(KC_6)), G(S(KC_7)), G(S(KC_8)), G(S(KC_9)), G(S(KC_0)),  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                 KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

// ─── Chordal Hold (opposite-hand rule for home row mods) ────────────────────

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x6_3(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',  '*', '*', '*'
    );

// ─── Tap Dance Definitions ──────────────────────────────────────────────────

void td_sym_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            layer_on(_SYMBOLS);
        } else {
            set_oneshot_layer(_SYMBOLS, ONESHOT_START);
        }
    } else if (state->count == 2) {
        layer_on(_NUMBERS);
    }
}

void td_sym_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            layer_off(_SYMBOLS);
        } else {
            clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
    } else if (state->count == 2) {
        layer_off(_NUMBERS);
    }
}

void td_spc_sym_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            layer_on(_SYMBOLS);
        } else {
            tap_code(KC_SPC);
        }
    }
}

void td_spc_sym_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
        layer_off(_SYMBOLS);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SYM_LAYER]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_sym_finished, td_sym_reset),
    [TD_SPC_SYM]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_spc_sym_finished, td_spc_sym_reset),
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};

// ─── Last Key Tracking ──────────────────────────────────────────────────────

static char last_key_char = 0;

static char keycode_to_char(uint16_t keycode, uint8_t mods) {
    if (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) {
        keycode = keycode & 0xFF;
    } else if (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) {
        keycode = keycode & 0xFF;
    }
    bool shifted = mods & MOD_MASK_SHIFT;
    if (keycode >= KC_A && keycode <= KC_Z) {
        return shifted ? ('A' + (keycode - KC_A)) : ('a' + (keycode - KC_A));
    }
    if (keycode >= KC_1 && keycode <= KC_9) return '1' + (keycode - KC_1);
    if (keycode == KC_0) return '0';
    if (keycode == KC_MINS) return shifted ? '_' : '-';
    if (keycode == KC_EQL)  return shifted ? '+' : '=';
    if (keycode == KC_LBRC) return shifted ? '{' : '[';
    if (keycode == KC_RBRC) return shifted ? '}' : ']';
    if (keycode == KC_BSLS) return shifted ? '|' : '\\';
    if (keycode == KC_SCLN) return shifted ? ':' : ';';
    if (keycode == KC_QUOT) return shifted ? '"' : '\'';
    if (keycode == KC_GRV)  return shifted ? '~' : '`';
    if (keycode == KC_COMM) return shifted ? '<' : ',';
    if (keycode == KC_DOT)  return shifted ? '>' : '.';
    if (keycode == KC_SLSH) return shifted ? '?' : '/';
    return 0;
}

// ─── Per-Key Tapping Term ──────────────────────────────────────────────────
// Home row mod-taps get a longer tapping term (300ms) to avoid false holds.
// Everything else uses the default (180ms).

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (IS_QK_MOD_TAP(keycode)) {
        return 300;
    }
    return TAPPING_TERM;
}

// ─── Mash Guard + Custom Keycodes ──────────────────────────────────────────

static uint16_t mash_last_event_time = 0;
static uint16_t mash_last_keycode    = KC_NO;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Mash guard: suppress accidental simultaneous keypresses
        bool prev_is_special = (mash_last_keycode >= QK_MOD_TAP   && mash_last_keycode <= QK_MOD_TAP_MAX) ||
                               (mash_last_keycode >= QK_LAYER_TAP && mash_last_keycode <= QK_LAYER_TAP_MAX);
        bool curr_is_special = (keycode >= QK_MOD_TAP   && keycode <= QK_MOD_TAP_MAX) ||
                               (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX);

        if (!prev_is_special && !curr_is_special &&
            TIMER_DIFF_16(record->event.time, mash_last_event_time) < MASH_GUARD_TERM) {
            return false;
        }

        mash_last_event_time = record->event.time;
        mash_last_keycode    = keycode;

        // Platform-aware clipboard keycodes
        uint8_t base = get_highest_layer(default_layer_state);
        bool win_mode = (base == _QWERTY_WIN || base == _GALLIUM_WIN);

        switch (keycode) {
            case CK_UNDO:
                tap_code16(win_mode ? C(KC_Z) : G(KC_Z));
                return false;
            case CK_CUT:
                tap_code16(win_mode ? C(KC_X) : G(KC_X));
                return false;
            case CK_COPY:
                tap_code16(win_mode ? C(KC_C) : G(KC_C));
                return false;
            case CK_PASTE:
                tap_code16(win_mode ? C(KC_V) : G(KC_V));
                return false;
        }

        // Last key tracking for OLED
        char c = keycode_to_char(keycode, get_mods());
        if (c) last_key_char = c;
    }
    return true;
}

// ─── OLED Display (graphical vertical layout, 32x128) ────────────────────────

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

extern const unsigned char font[] PROGMEM;

// ─── Modifier Icon Bitmaps (14x14, row-major, 2 bytes/row in PROGMEM) ───────

static const uint8_t PROGMEM icon_shift_filled[] = {
    0x03,0x00, 0x07,0x80, 0x0F,0xC0, 0x1F,0xE0,
    0x3F,0xF0, 0x7F,0xF8, 0x03,0x00, 0x03,0x00,
    0x03,0x00, 0x03,0x00, 0x03,0x00, 0x0F,0xC0,
    0x0F,0xC0, 0x00,0x00,
};
static const uint8_t PROGMEM icon_shift_small[] = {
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x03,0x00, 0x07,0x80, 0x0F,0xC0, 0x03,0x00,
    0x03,0x00, 0x07,0x80, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00,
};
static const uint8_t PROGMEM icon_ctrl_filled[] = {
    0x07,0x80, 0x0C,0xC0, 0x18,0x60, 0x30,0x30,
    0x60,0x18, 0xC0,0x0C, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00,
};
static const uint8_t PROGMEM icon_ctrl_small[] = {
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x03,0x00, 0x04,0x80, 0x08,0x40, 0x00,0x00,
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00,
};
static const uint8_t PROGMEM icon_opt_filled[] = {
    0x00,0x00, 0xC0,0x3C, 0x60,0x3C, 0x30,0x00,
    0x18,0x00, 0x0C,0x00, 0x06,0x00, 0x03,0x00,
    0x01,0x80, 0x00,0xC0, 0x00,0x60, 0x00,0x30,
    0x00,0x1C, 0x00,0x0C,
};
static const uint8_t PROGMEM icon_opt_small[] = {
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x09,0xC0, 0x05,0xC0, 0x02,0x00, 0x01,0x00,
    0x00,0x80, 0x00,0x40, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00,
};
static const uint8_t PROGMEM icon_cmd_filled[] = {
    0x70,0xE0, 0x89,0x10, 0x89,0x10, 0x76,0xE0,
    0x16,0x80, 0x10,0x80, 0x76,0xE0, 0x89,0x10,
    0x89,0x10, 0x70,0xE0, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00,
};
static const uint8_t PROGMEM icon_cmd_small[] = {
    0x00,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00,
    0x04,0x80, 0x0B,0x40, 0x04,0x80, 0x04,0x80,
    0x0B,0x40, 0x04,0x80, 0x00,0x00, 0x00,0x00,
    0x00,0x00, 0x00,0x00,
};

// ─── Rendering Helpers ───────────────────────────────────────────────────────

static void render_icon_14x14(uint8_t x, uint8_t y, const uint8_t *icon) {
    for (uint8_t row = 0; row < 14; row++) {
        uint8_t b0 = pgm_read_byte(&icon[row * 2]);
        uint8_t b1 = pgm_read_byte(&icon[row * 2 + 1]);
        for (uint8_t col = 0; col < 8; col++)
            oled_write_pixel(x + col, y + row, (b0 >> (7 - col)) & 1);
        for (uint8_t col = 0; col < 6; col++)
            oled_write_pixel(x + 8 + col, y + row, (b1 >> (7 - col)) & 1);
    }
}

static void render_scaled_char(uint8_t x, uint8_t y, char c, uint8_t scale) {
    const uint8_t *glyph = &font[(uint8_t)c * OLED_FONT_WIDTH];
    for (uint8_t col = 0; col < 5; col++) {
        uint8_t col_data = pgm_read_byte(&glyph[col]);
        for (uint8_t row = 0; row < 8; row++) {
            bool on = (col_data >> row) & 1;
            for (uint8_t dx = 0; dx < scale; dx++)
                for (uint8_t dy = 0; dy < scale; dy++)
                    oled_write_pixel(x + col * scale + dx, y + row * scale + dy, on);
        }
    }
}

static void clear_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    for (uint8_t py = y; py < y + h; py++)
        for (uint8_t px = x; px < x + w; px++)
            oled_write_pixel(px, py, false);
}

static const char *get_layer_name(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _GALLIUM:
        case _QWERTY_WIN:
        case _GALLIUM_WIN: return "Base";
        case _NUMBERS:     return "Numbr";
        case _NAV:         return "Nav";
        case _SYMBOLS:     return "Symbl";
        case _FKEYS:       return "FKeys";
        default:           return "?????";
    }
}

static const char *get_layout_name(void) {
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:      return "QWRTY";
        case _GALLIUM:     return "GALLM";
        case _QWERTY_WIN:  return "QWWIN";
        case _GALLIUM_WIN: return "GLWIN";
        default:           return "?????";
    }
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) return false;

    // Layout name (Y=0-7, text row 0)
    oled_set_cursor(0, 0);
    oled_write_ln(get_layout_name(), false);

    // Layer name (Y=8-15, text row 1)
    oled_set_cursor(0, 1);
    oled_write_ln(get_layer_name(), false);

    // Modifier icons: 2x2 grid (Y=18-47)
    uint8_t mods = get_mods() | get_oneshot_mods();
    render_icon_14x14(1, 18,  (mods & MOD_MASK_SHIFT) ? icon_shift_filled : icon_shift_small);
    render_icon_14x14(17, 18, (mods & MOD_MASK_CTRL)  ? icon_ctrl_filled  : icon_ctrl_small);
    render_icon_14x14(1, 34,  (mods & MOD_MASK_ALT)   ? icon_opt_filled   : icon_opt_small);
    render_icon_14x14(17, 34, (mods & MOD_MASK_GUI)   ? icon_cmd_filled   : icon_cmd_small);

    // Large last key character (Y=52-75, 3x scaled = 15x24 at x=8)
    clear_rect(8, 52, 15, 24);
    if (last_key_char) {
        render_scaled_char(8, 52, last_key_char, 3);
    }

    // Caps Word indicator (Y=80-87, text row 10)
    oled_set_cursor(0, 10);
    oled_write_ln_P(is_caps_word_on() ? PSTR("  CW") : PSTR(""), false);

    // WPM digits (Y=96-109, 2x scaled = 10x14 per digit)
    char wpm_str[4];
    snprintf(wpm_str, sizeof(wpm_str), "%3d", get_current_wpm());
    render_scaled_char(1, 96, wpm_str[0], 2);
    render_scaled_char(11, 96, wpm_str[1], 2);
    render_scaled_char(21, 96, wpm_str[2], 2);

    // WPM label (Y=112-119, text row 14)
    oled_set_cursor(0, 14);
    oled_write_ln_P(PSTR(" WPM"), false);

    return false;
}

#endif // OLED_ENABLE
