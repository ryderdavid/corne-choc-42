// Corne Choc 42-Key — Gallium v1 Profile (Windows Mode)
// Windows-optimized with SGAC home row mods + word chording + enhanced OLED
//
// Gallium v1 alpha layout:
//   b l d c v   j y o u -
//   n r t s g   p h a e i
//   q x m w z   k f , . '
//
// Layers:
//   0 = Base (Gallium v1)
//   1 = Lower (numbers, F-keys, symbols)
//   2 = Raise (navigation, editing, media)
//   3 = Symbols (activated by Lower+Raise)

#include QMK_KEYBOARD_H
#include <stdio.h>

// ─── Layer Names ────────────────────────────────────────────────────────────

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _SYMBOLS,
    _FKEYS,
};

// ─── Home Row Mods — SGAC (Shift-Gui/Win-Alt-Ctrl) ──────────────────────────

// Left hand (Gallium home row: N R T S G)
#define HM_N    LSFT_T(KC_N)
#define HM_R    LGUI_T(KC_R)
#define HM_T    LALT_T(KC_T)
#define HM_S    LCTL_T(KC_S)

// Right hand (Gallium home row: P H A E I)
#define HM_P    RCTL_T(KC_P)
#define HM_A    RALT_T(KC_A)
#define HM_E    RGUI_T(KC_E)
#define HM_I    RSFT_T(KC_I)

// ─── Thumb Keys ─────────────────────────────────────────────────────────────

#define LW_SPC  LT(_LOWER, KC_SPC)
#define RS_ENT  LT(_RAISE, KC_ENT)
#define FK_ENT  LT(_FKEYS, KC_ENT)
#define NV_TAB  LT(_RAISE, KC_TAB)

// ─── Combo Definitions ──────────────────────────────────────────────────────

enum combo_events {
    // Utility combos
    CMB_ESC,          // Tab+B = Escape
    CMB_DEL,          // S+T = Delete
    CMB_BSPC,         // H+A = Backspace
    CMB_HYPER_Z,      // Shift+Q = Hyper+Z
    CMB_NAV_BACK,     // J+Y = Cmd+[ (Y+U position)
    CMB_NAV_FWD,      // -+Bksp = Cmd+] (P+Bksp position)

    // Word chords (Space + letter keys)
    WC_THE,  WC_BE,   WC_TO,   WC_AND,  WC_OF,
    WC_IN,   WC_HAVE, WC_THAT, WC_FOR,  WC_NOT,
    WC_WITH, WC_YOU,  WC_THIS, WC_FROM, WC_BUT,
    WC_WHAT, WC_IT,   WC_HE,   WC_ON,   WC_ARE,
    WC_DO,   WC_HIS,  WC_BY,   WC_THEY, WC_HER,
    WC_OR,   WC_AT,   WC_ONE,  WC_HAD,  WC_SAY,
    WC_SHE,  WC_ALL,  WC_WHICH,WC_WILL, WC_WOULD,
    WC_THERE,WC_THEIR,WC_MY,   WC_OUT,  WC_UP,
    WC_ABOUT,WC_WHO,  WC_GET,  WC_MAKE, WC_GO,
    WC_LIKE, WC_JUST, WC_KNOW, WC_TAKE, WC_COME,

    COMBO_COUNT
};

// Include combo key arrays
#include "combos.def"

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;
    switch (combo_index) {
        case WC_THE:   SEND_STRING("the "); break;
        case WC_BE:    SEND_STRING("be "); break;
        case WC_TO:    SEND_STRING("to "); break;
        case WC_AND:   SEND_STRING("and "); break;
        case WC_OF:    SEND_STRING("of "); break;
        case WC_IN:    SEND_STRING("in "); break;
        case WC_HAVE:  SEND_STRING("have "); break;
        case WC_THAT:  SEND_STRING("that "); break;
        case WC_FOR:   SEND_STRING("for "); break;
        case WC_NOT:   SEND_STRING("not "); break;
        case WC_WITH:  SEND_STRING("with "); break;
        case WC_YOU:   SEND_STRING("you "); break;
        case WC_THIS:  SEND_STRING("this "); break;
        case WC_FROM:  SEND_STRING("from "); break;
        case WC_BUT:   SEND_STRING("but "); break;
        case WC_WHAT:  SEND_STRING("what "); break;
        case WC_IT:    SEND_STRING("it "); break;
        case WC_HE:    SEND_STRING("he "); break;
        case WC_ON:    SEND_STRING("on "); break;
        case WC_ARE:   SEND_STRING("are "); break;
        case WC_DO:    SEND_STRING("do "); break;
        case WC_HIS:   SEND_STRING("his "); break;
        case WC_BY:    SEND_STRING("by "); break;
        case WC_THEY:  SEND_STRING("they "); break;
        case WC_HER:   SEND_STRING("her "); break;
        case WC_OR:    SEND_STRING("or "); break;
        case WC_AT:    SEND_STRING("at "); break;
        case WC_ONE:   SEND_STRING("one "); break;
        case WC_HAD:   SEND_STRING("had "); break;
        case WC_SAY:   SEND_STRING("say "); break;
        case WC_SHE:   SEND_STRING("she "); break;
        case WC_ALL:   SEND_STRING("all "); break;
        case WC_WHICH: SEND_STRING("which "); break;
        case WC_WILL:  SEND_STRING("will "); break;
        case WC_WOULD: SEND_STRING("would "); break;
        case WC_THERE: SEND_STRING("there "); break;
        case WC_THEIR: SEND_STRING("their "); break;
        case WC_MY:    SEND_STRING("my "); break;
        case WC_OUT:   SEND_STRING("out "); break;
        case WC_UP:    SEND_STRING("up "); break;
        case WC_ABOUT: SEND_STRING("about "); break;
        case WC_WHO:   SEND_STRING("who "); break;
        case WC_GET:   SEND_STRING("get "); break;
        case WC_MAKE:  SEND_STRING("make "); break;
        case WC_GO:    SEND_STRING("go "); break;
        case WC_LIKE:  SEND_STRING("like "); break;
        case WC_JUST:  SEND_STRING("just "); break;
        case WC_KNOW:  SEND_STRING("know "); break;
        case WC_TAKE:  SEND_STRING("take "); break;
        case WC_COME:  SEND_STRING("come "); break;
    }
}

// ─── Keymaps ────────────────────────────────────────────────────────────────

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Base — Gallium v1 with SGAC home row mods (Windows)                 │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // ,--------------------------------------------.  ,--------------------------------------------.
    // | `  ~ |  B   |  L   |  D   |  C   |  V     |  |  J   |  Y   |  O   |  U   |  -   | Bspc   |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | Tab  |  N   |  R   |  T   |  S   |  G     |  |  P   |  H   |  A   |  E   |  I   |  ;     |
    // | /Rse | Sft  | Win  | Alt  | Ctl  |        |  | Ctl  |      | Alt  | Win  | Sft  |        |
    // |------+------+------+------+------+---------|  |------+------+------+------+------+---------|
    // | Sft  |  Q   |  X   |  M   |  W   |  Z     |  |  K   |  F   |  ,   |  .   |  '   | Sft    |
    // `------+------+------+------+------+---------'  `---------+------+------+------+------+------'
    //                      | Alt  | Ctl  | Lwr/ |      | Rse/ | Ctl  | Alt  |
    //                      |      |      | Spc  |      | Ent  |      |      |
    //                      `--------------------'      `--------------------'

    [_BASE] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_B,    KC_L,    KC_D,    KC_C,    KC_V,         KC_J,    KC_Y,    KC_O,    KC_U,    KC_MINS, KC_BSPC,
        NV_TAB,  HM_N,    HM_R,    HM_T,    HM_S,    KC_G,         HM_P,    KC_H,    HM_A,    HM_E,    HM_I,    LT(_SYMBOLS,KC_SCLN),
        KC_LSFT, KC_Q,    KC_X,    KC_M,    KC_W,    KC_Z,         KC_K,    KC_F,    KC_COMM, KC_DOT,  KC_QUOT, KC_RSFT,
                                    KC_LALT, KC_LCTL, LW_SPC,       RS_ENT,  KC_RCTL, FK_ENT
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Lower — Numbers, F-keys, symbols                                    │
    // └──────────────────────────────────────────────────────────────────────┘

    [_LOWER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_TRNS, KC_DOT,  KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      MO(_SYMBOLS), KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Raise — Navigation, editing, media                                  │
    // └──────────────────────────────────────────────────────────────────────┘
    //
    // Clipboard shortcuts use Ctrl (Windows standard)
    // Mods row follows SGAC order: Shift, Win, Alt, Ctrl

    [_RAISE] = LAYOUT_split_3x6_3(
        KC_ESC,  C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_NO,        KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_NO,   KC_DEL,
        KC_TRNS, KC_LSFT, KC_LGUI, KC_LALT, KC_LCTL, KC_NO,        KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_ENT,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_MPLY, KC_NO,        KC_NO,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                                    KC_TRNS, KC_TRNS, MO(_SYMBOLS), KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ Symbols (activated by Lower + Raise)                                │
    // └──────────────────────────────────────────────────────────────────────┘

    [_SYMBOLS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_LABK, KC_LCBR, KC_LBRC, KC_MINS, KC_RGHT, KC_TRNS,
        KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,      KC_RABK, KC_RCBR, KC_RBRC, KC_EQL,  KC_PIPE, KC_TRNS,
        KC_TRNS, KC_SCLN, KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,      KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, KC_BSLS, KC_TRNS,
                                    KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS
    ),

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │ F-Keys — F1-F12 on left hand (held via right outer thumb)           │
    // └──────────────────────────────────────────────────────────────────────┘

    [_FKEYS] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11,  KC_F12,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
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

// ─── Mash Guard ─────────────────────────────────────────────────────────────
// Uses the original hardware event timestamp to detect truly simultaneous
// accidental keypresses (typically < 5ms apart). Bypasses for mod-tap and
// layer-tap keys so home row mods and thumb keys are never affected.

static uint16_t mash_last_event_time = 0;
static uint16_t mash_last_keycode    = KC_NO;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        bool prev_is_special = (mash_last_keycode >= QK_MOD_TAP   && mash_last_keycode <= QK_MOD_TAP_MAX) ||
                               (mash_last_keycode >= QK_LAYER_TAP && mash_last_keycode <= QK_LAYER_TAP_MAX);
        bool curr_is_special = (keycode >= QK_MOD_TAP   && keycode <= QK_MOD_TAP_MAX) ||
                               (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX);

        if (!prev_is_special && !curr_is_special &&
            TIMER_DIFF_16(record->event.time, mash_last_event_time) < MASH_GUARD_TERM) {
            return false;  // suppress accidental simultaneous press
        }

        mash_last_event_time = record->event.time;
        mash_last_keycode    = keycode;

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

// Full-size (14x14) when ACTIVE, tiny (6x6 centered) when INACTIVE
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
        case _BASE:    return "Base";
        case _LOWER:   return "Lower";
        case _RAISE:   return "Raise";
        case _SYMBOLS: return "Symbl";
        case _FKEYS:   return "FKeys";
        default:       return "?????";
    }
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) return false;

    oled_set_cursor(0, 0);
    oled_write_ln_P(PSTR("GLWIN"), false);

    oled_set_cursor(0, 1);
    oled_write_ln(get_layer_name(), false);

    uint8_t mods = get_mods() | get_oneshot_mods();
    render_icon_14x14(1, 18,  (mods & MOD_MASK_SHIFT) ? icon_shift_filled : icon_shift_small);
    render_icon_14x14(17, 18, (mods & MOD_MASK_CTRL)  ? icon_ctrl_filled  : icon_ctrl_small);
    render_icon_14x14(1, 34,  (mods & MOD_MASK_ALT)   ? icon_opt_filled   : icon_opt_small);
    render_icon_14x14(17, 34, (mods & MOD_MASK_GUI)   ? icon_cmd_filled   : icon_cmd_small);

    clear_rect(8, 52, 15, 24);
    if (last_key_char) {
        render_scaled_char(8, 52, last_key_char, 3);
    }

    oled_set_cursor(0, 10);
    oled_write_ln_P(is_caps_word_on() ? PSTR("  CW") : PSTR(""), false);

    char wpm_str[4];
    snprintf(wpm_str, sizeof(wpm_str), "%3d", get_current_wpm());
    render_scaled_char(1, 96, wpm_str[0], 2);
    render_scaled_char(11, 96, wpm_str[1], 2);
    render_scaled_char(21, 96, wpm_str[2], 2);

    oled_set_cursor(0, 14);
    oled_write_ln_P(PSTR(" WPM"), false);

    return false;
}

#endif // OLED_ENABLE
