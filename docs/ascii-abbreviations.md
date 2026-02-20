# ASCII Layout Abbreviation Rules

All labels are **4 characters wide**, right-padded with spaces if shorter.

## Basic Keys

| QMK Keycode | Label | Notes |
|---|---|---|
| `KC_A` | `  A ` | Single letter, centered |
| `KC_1` | `  1 ` | Number |
| `KC_F1` | ` F1 ` | Function key |
| `KC_F10` | ` F10` | Function key (wider) |
| `KC_TAB` | `TAB ` | |
| `KC_BSPC` | `BSPC` | Backspace |
| `KC_DEL` | `DEL ` | Delete |
| `KC_ESC` | `ESC ` | Escape |
| `KC_ENT` | `ENT ` | Enter/Return |
| `KC_SPC` | `SPC ` | Space |
| `KC_CAPS` | `CAPS` | Caps Lock |

## Modifiers

| QMK Keycode | Label | Notes |
|---|---|---|
| `KC_LSFT` | `LSFT` | Left Shift |
| `KC_RSFT` | `RSFT` | Right Shift |
| `KC_LCTL` | `LCTL` | Left Control |
| `KC_RCTL` | `RCTL` | Right Control |
| `KC_LALT` / `KC_LOPT` | `LALT` | Left Alt/Option |
| `KC_RALT` / `KC_ROPT` | `RALT` | Right Alt/Option |
| `KC_LGUI` / `KC_LCMD` | `LGUI` | Left Cmd/Win |
| `KC_RGUI` / `KC_RCMD` | `RGUI` | Right Cmd/Win |

## Symbols

| QMK Keycode | Label | Notes |
|---|---|---|
| `KC_GRV` | ` `~ ` | Grave/tilde |
| `KC_MINS` | `  - ` | |
| `KC_EQL` | `  = ` | |
| `KC_LBRC` | `  [ ` | Left bracket |
| `KC_RBRC` | `  ] ` | Right bracket |
| `KC_BSLS` | `  \ ` | Backslash |
| `KC_SCLN` | `  ; ` | Semicolon |
| `KC_QUOT` | `  ' ` | Quote |
| `KC_COMM` | `  , ` | Comma |
| `KC_DOT` | `  . ` | Period |
| `KC_SLSH` | `  / ` | Forward slash |
| `KC_EXLM` | `  ! ` | |
| `KC_AT` | `  @ ` | |
| `KC_HASH` | `  # ` | |
| `KC_DLR` | `  $ ` | |
| `KC_PERC` | `  % ` | |
| `KC_CIRC` | `  ^ ` | |
| `KC_AMPR` | `  & ` | |
| `KC_ASTR` | `  * ` | |
| `KC_LPRN` | `  ( ` | |
| `KC_RPRN` | `  ) ` | |
| `KC_UNDS` | `  _ ` | |
| `KC_PLUS` | `  + ` | |
| `KC_LCBR` | `  { ` | Left brace |
| `KC_RCBR` | `  } ` | Right brace |
| `KC_PIPE` | ` \| ` | Pipe |
| `KC_TILD` | `  ~ ` | |

## Navigation

| QMK Keycode | Label | Notes |
|---|---|---|
| `KC_UP` | `  ↑ ` | Up arrow |
| `KC_DOWN` | `  ↓ ` | Down arrow |
| `KC_LEFT` | `  ← ` | Left arrow |
| `KC_RGHT` | `  → ` | Right arrow |
| `KC_HOME` | `HOME` | |
| `KC_END` | `END ` | |
| `KC_PGUP` | `PGUP` | |
| `KC_PGDN` | `PGDN` | |

## Media

| QMK Keycode | Label | Notes |
|---|---|---|
| `KC_VOLU` | `VOL+` | |
| `KC_VOLD` | `VOL-` | |
| `KC_MUTE` | `MUTE` | |
| `KC_MPLY` | `P/P ` | Play/Pause |
| `KC_MNXT` | `NEXT` | |
| `KC_MPRV` | `PREV` | |
| `KC_BRIU` | `BRI+` | |
| `KC_BRID` | `BRI-` | |

## Hold-Tap / Mod-Tap

Format: **2-char modifier abbreviation** + `/` + **1-char tap key**

| Modifier | Abbreviation |
|---|---|
| Shift | `sh` |
| Control | `ct` |
| Alt/Option | `op` |
| GUI/Cmd | `cm` |
| Hyper | `hy` |
| Meh | `me` |

Examples:
| QMK | Label | Meaning |
|---|---|---|
| `LSFT_T(KC_A)` | `sh/A` | Hold=Shift, Tap=A |
| `LCTL_T(KC_S)` | `ct/S` | Hold=Ctrl, Tap=S |
| `LALT_T(KC_D)` | `op/D` | Hold=Option, Tap=D |
| `LGUI_T(KC_F)` | `cm/F` | Hold=Cmd, Tap=F |

## Layer-Tap

Format: **2-char layer abbreviation** + `/` + **1-char tap key**

| Layer | Abbreviation |
|---|---|
| LOWER | `LW` |
| RAISE | `RS` |
| ADJUST | `AJ` |

Examples:
| QMK | Label | Meaning |
|---|---|---|
| `LT(_LOWER, KC_SPC)` | `LW/S` | Hold=Lower, Tap=Space |
| `LT(_RAISE, KC_ENT)` | `RS/E` | Hold=Raise, Tap=Enter |

## Momentary / Toggle Layer

| QMK | Label | Notes |
|---|---|---|
| `MO(_LOWER)` | ` LWR` | Momentary layer |
| `MO(_RAISE)` | ` RSE` | |
| `TG(_ADJUST)` | `tADJ` | Toggle |

## Special

| QMK | Label | Notes |
|---|---|---|
| `KC_TRNS` | ` ___` | Transparent (fall through) |
| `KC_NO` | ` XXX` | Blocked/no action |
| `CW_TOGG` | `CWRD` | Caps Word |
| `QK_BOOT` | `BOOT` | Bootloader |
| `QK_RBT` | `RBOT` | Reboot |

## macOS Shortcuts

| QMK | Label | Notes |
|---|---|---|
| `G(KC_Z)` | ` ⌘Z ` | Cmd+Z (Undo) |
| `G(KC_X)` | ` ⌘X ` | Cmd+X (Cut) |
| `G(KC_C)` | ` ⌘C ` | Cmd+C (Copy) |
| `G(KC_V)` | ` ⌘V ` | Cmd+V (Paste) |
