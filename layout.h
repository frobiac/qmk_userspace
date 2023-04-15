// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

// This file is *not at all* included when using QMK compile '-kb frobiac/blackbowl -km default' syntax!
// @TODO : Figure out how to use with json compile, enum instead of define, ...

#pragma once

// Do *NOT* include, as MAX will be redefined
// #include "quantum.h"

// Note this kludge is required to be able to
// compile *both* regular keymaps in the keyboards' directory
// *and* JSON configs here in userspace!
// Still fails when CONSOLE_ENABLE is not set?
#ifndef __ASSEMBLER__
// Using default german keymap include does *NOT* work because it includes "keymap.h".
// Even with the above __ASSEMBLER__ guard, building '-kb frobiac/blackbowl -km frobiac' fails here with
// #include "keymap_german.h"
//
#    include "keymap_german_no_include.h"

enum layers {
    _FROBIAC,
    _QWERTZ,
    _SYMBOLS,
    _NAVNUM,
    _FUNC,
    _MOUSE,
};

#    if defined(VIAL_ENABLE) || defined(JSON_COMPILE)
#        define MY_SAFE_RANGE 0x5F10
#    endif

// when #include "quantum_keycodes.h" is used, MAX and xprintf are redefined, apparently
enum custom_keycodes {
    // Neither SAFE_RANGE or UNICODE_EMACS + 1 work here if quantum_keycodes.h isn't included,
    // which in turn would cause MAX and xprintf re-definition errors without patching VIAL/QMK core!
    // SAFE_RANGE, same as default QK_USER in QMK, not available in VIAL
    REC_START = MY_SAFE_RANGE,
    REC_STOP,
    REC_REPLAY,
    XOR_INIT,
    XOR_PLAY,
    TP_RESET,
};

#endif
// Contains a layout based on 'Aus der Neo-Welt', 'NordTast' and 'Neo' extra layers

// Support
// 4x12  : HyperNano (2x2 unused)
// 3x5_3 : CrowBoard, cantor
// 3x5_2 : Sweep
// 4x5   : BlackBowl (3 thumbs, 1 extra upper right,  2x1 unused ring finger)
// 4x6   : RedTilt (see BlackBowl plus extra column)

/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off

#define LAYOUT_hypernano_4x12_wrapper(...)  LAYOUT_hypernano_4x12(__VA_ARGS__)
#define LAYOUT_redtilt_4x12_wrapper(...)    LAYOUT_redtilt_4x12(__VA_ARGS__)
#define LAYOUT_blackbowl_4x12_wrapper(...)  LAYOUT_blackbowl_4x12(__VA_ARGS__)
#define LAYOUT_blackflat_4x12_wrapper(...)  LAYOUT_blackflat_4x12(__VA_ARGS__)
#define LAYOUT_sweep_3x5_2_wrapper(...)     LAYOUT_sweep_3x5_2(__VA_ARGS__)
#define LAYOUT_crowboard_3x5_3_wrapper(...) LAYOUT_crowboard_3x5_3(__VA_ARGS__)
#define LAYOUT_chocofi_3x5_3_wrapper(...)   LAYOUT_chocofi_3x5_3(__VA_ARGS__)



#define IS_COMMAND() (((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) == MOD_MASK_SHIFT)

// Cosmetic only: To neatly fit into 7 chars
#define _L_MOUS MO(_MOUSE)
#define _L_FUNC MO(_FUNC)

// @TODO: Use defines for any key-combination that is checked in process_record_.. routines to
//        avoid issues on change.
#define _MOUS_X LT(_MOUSE, KC_X)
#define _MOUS_Y LT(_MOUSE, DE_Y)
#define _FUNC_Z LT(_FUNC,  DE_Z)

#define _NAVESC LT(_NAVNUM, KC_ESC)
#define _SYMENT LT(_SYMBOLS, KC_ENT)

#define _______THUMBS_L_x3_______                           KC_LGUI,   LCTL_T(KC_TAB),      LALT_T(KC_SPC)
#define _______THUMBS_R_x3_______                           _NAVESC,   LSFT_T(KC_BSPC),     _SYMENT

#define _________________THUMBS_TRNS_x5____________         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS


#define _________________FROBIAC_L1________________         KC_K,    KC_U,    KC_Q,    KC_DOT,  KC_J
#define _________________FROBIAC_L2________________         KC_H,    KC_I,    KC_E,    KC_A,    KC_O
#define _________________FROBIAC_L3________________         _MOUS_X, DE_Y,    DE_MINS, KC_COMM, DE_SLSH

#define _________________FROBIAC_R1________________         KC_P,    KC_C,    KC_L,    KC_M,    KC_F
#define _________________FROBIAC_R2________________         KC_D,    KC_T,    KC_R,    KC_N,    KC_S
#define _________________FROBIAC_R3________________         KC_B,    KC_G,    KC_W,    KC_V,    _FUNC_Z

#define _________________QWERTZ__L1________________         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTZ__L2________________         KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTZ__L3________________         _MOUS_Y, KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTZ__R1________________         DE_Z,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTZ__R2________________         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTZ__R3________________         KC_N,    KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_SLASH)


#define _________________SYMBOLS_L1________________         DE_AT,   DE_DEG,  DE_LBRC, DE_RBRC, DE_HASH
#define _________________SYMBOLS_L2________________         DE_BSLS, DE_EURO, DE_LCBR, DE_RCBR, DE_ASTR
#define _________________SYMBOLS_L3________________         XXXXXXX, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV

#define _________________SYMBOLS_R1________________         DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR
#define _________________SYMBOLS_R2________________         DE_QUES, DE_LPRN, DE_RPRN, DE_PLUS, KC_ENT
#define _________________SYMBOLS_R3________________         DE_CIRC, DE_PERC, DE_DQUO, DE_QUOT, XXXXXXX


#define _________________NAV_NUM_L1________________         KC_PGUP, KC_BSPC,  KC_UP,  KC_DEL,  KC_PGDN
#define _________________NAV_NUM_L2________________         KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END
#define _________________NAV_NUM_L3________________         XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, XXXXXXX

#define _________________NAV_NUM_R1________________         DE_SS,   KC_7,    KC_8,    KC_9,    DE_ADIA
#define _________________NAV_NUM_R2________________         KC_DOT,  KC_4,    KC_5,    KC_6,    DE_ODIA
#define _________________NAV_NUM_R3________________         KC_0,    KC_1,    KC_2,    KC_3,    DE_UDIA


#define _________________FUNC_FX_L1________________         ____RECORDING_x3_________, DF(_QWERTZ), DF(_FROBIAC)
#define _________________FUNC_FX_L2________________         ____DYNAMIC_MACRO_1_x3___, XXXXXXX, QK_REBOOT
#define _________________FUNC_FX_L3________________         TP_RESET, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOTLOADER

#define _________________FUNC_FX_R1________________         XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10
#define _________________FUNC_FX_R2________________         XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11
#define _________________FUNC_FX_R3________________         XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12


#define _________________MOUSE___L1________________         KC_WH_L, KC_BTN1, KC_MS_U, KC_BTN3, KC_BTN2
#define _________________MOUSE___L2________________         KC_WH_R, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U
#define _________________MOUSE___L3________________         _MOUS_X, KC_BTN1, KC_BTN3, KC_BTN2, KC_WH_D

// @TODO MOUSE Scroll lock on other than BTN3 (default)?
#define _________________MOUSE___R1________________         KC_ACL0, XXXXXXX, KC_BTN3, XXXXXXX, KC_BTN5
#define _________________MOUSE___R2________________         KC_ACL1, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN4
#define _________________MOUSE___R3________________         KC_ACL2, XXXXXXX, XXXXXXX, QK_REBOOT, QK_BOOT


#if defined(DYNAMIC_MACRO_ENABLE)
#    define ____DYNAMIC_MACRO_1_x3___ DM_REC1, DM_RSTP, DM_PLY1
#else
#    define ____DYNAMIC_MACRO_1_x3___ KC_TRNS, KC_TRNS, KC_TRNS
#endif

#if defined(FEAT_RECORDING)
#    define ____RECORDING_x3_________ REC_START, REC_STOP, REC_REPLAY
#else
#    define ____RECORDING_x3_________ KC_TRNS, KC_TRNS, KC_TRNS
#endif

/// All basic components describe 2 sides of 4x5 keys.
/// Most custom boards miss one key in the ring finger columns on the bottom most row:
/// might be hooked up via a tiny pushbutton like on blackflat, but not generally used.
/// The outer matrix positions in the thumb row are located on the _top_ row on all split boards
///
/// The HyperNano has 2x2 extra keys in the center of the bottom two rows.
/// The RedTilt has one extra pinky column on each side.
#define _FROBIAC_L \
    _________________FROBIAC_L1________________, _________________FROBIAC_R1________________, \
    _________________FROBIAC_L2________________, _________________FROBIAC_R2________________, \
    _________________FROBIAC_L3________________, _________________FROBIAC_R3________________, \
    KC_RALT, XXXXXXX, _______THUMBS_L_x3_______, _______THUMBS_R_x3_______, KC_RSFT, _L_FUNC

#define _QWERTZ_L \
    _________________QWERTZ__L1________________, _________________QWERTZ__R1________________, \
    _________________QWERTZ__L2________________, _________________QWERTZ__R2________________, \
    _________________QWERTZ__L3________________, _________________QWERTZ__R3________________, \
    KC_RALT, XXXXXXX, _______THUMBS_L_x3_______, _______THUMBS_R_x3_______, KC_RSFT, _L_FUNC

#define _SYMBOLS_L \
    _________________SYMBOLS_L1________________, _________________SYMBOLS_R1________________, \
    _________________SYMBOLS_L2________________, _________________SYMBOLS_R2________________, \
    _________________SYMBOLS_L3________________, _________________SYMBOLS_R3________________, \
    _________________THUMBS_TRNS_x5____________, _________________THUMBS_TRNS_x5____________

#define _NAVNUM_L \
    _________________NAV_NUM_L1________________, _________________NAV_NUM_R1________________, \
    _________________NAV_NUM_L2________________, _________________NAV_NUM_R2________________, \
    _________________NAV_NUM_L3________________, _________________NAV_NUM_R3________________, \
    _________________THUMBS_TRNS_x5____________, _________________THUMBS_TRNS_x5____________

#define _FUNC_L \
    _________________FUNC_FX_L1________________, _________________FUNC_FX_R1________________, \
    _________________FUNC_FX_L2________________, _________________FUNC_FX_R2________________, \
    _________________FUNC_FX_L3________________, _________________FUNC_FX_R3________________, \
    _________________THUMBS_TRNS_x5____________, _________________THUMBS_TRNS_x5____________

#define _MOUSE_L \
    _________________MOUSE___L1________________, _________________MOUSE___R1________________, \
    _________________MOUSE___L2________________, _________________MOUSE___R2________________, \
    _________________MOUSE___L3________________, _________________MOUSE___R3________________, \
    _________________THUMBS_TRNS_x5____________, _________________THUMBS_TRNS_x5____________


#define xxx KC_NO


 /*
    HyperNano custom board: 4 keys missing in matrix where trackpoint can be installed.
    Could also just use info.json, but this way reuse of convenience defines
    and default layers is easier to change for multiple boards
    8x6 matrix wired, but layout similar to a 4x12 board

    ┌─────┬───┬───┬───┬───┐───────┌───┬───┬───┬───┬─────┐
    │  00 │01 │02 │03 │04 │       │40 │41 │42 │43 │44   │
    ├────┬┴──┬┴──┬┴──┬┴──┬┘   _   └┬──┴┬──┴┬──┴┬──┴┬────┤
    │ 10 │11 │12 │13 │14 │   (_)   │50 │51 │52 │53 │54  │
    ├───┬┴──┬┴──┬┴──┬┴──┬┴──┐   ┌──┴┬──┴┬──┴┬──┴┬──┴┬───┤
    │20 │21 │22 │23 │24 │25 │   │65*│60 │61 │62 │63 │64 │
    ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┐ ┌┴──┬┴──┬┴──┬┴──┬┴──┬┴───┤
    │ 30 │31 │32 │33 │34 │35 │ │75*│70 │71 │72 │73 │74  │
    └────┴───┴───┴───┴───┴───┘─└───┴───┴───┴───┴───┴────┘
 */

// Use base plus the 4 HyperNano-specific keys at the end, but mapped to the center
#define LAYOUT_hypernano_4x12( \
    L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24, \
    L30, L31, L32, L33, L34,           R30, R31, R32, R33, R34, \
                             L25, R25, \
                             L35, R35  \
    ) \
    { \
        { L00, L01, L02, L03, L04, xxx }, \
        { L10, L11, L12, L13, L14, xxx }, \
        { L20, L21, L22, L23, L24, L25 }, \
        { L30, L31, L32, L33, L34, L35 }, \
        { R00, R01, R02, R03, R04, xxx }, \
        { R10, R11, R12, R13, R14, xxx }, \
        { R20, R21, R22, R23, R24, R25 }, \
        { R30, R31, R32, R33, R34, R35 } \
    }


/*
    BlackFlat: RedTilt without outer pinky columns, with 4th button on pinky bottom row
    and hooked up to former bluecube teensy with limited working pins
    BlackBowl: Identical layout-wise, but with I2C for both halves.

    (31), (73) and RST are PCB push-buttons

    ┌───┐   ┌───┬───┬───┐    ┌───┬───┬───┐RST┌───┐
    │30*├───┤02 │03 │04 │    │40 │41 │42 ├───┤74*│
    ├───┤01 ├───┼───┼───┤    ├─[TP]──┼───┤43 ├───┤
    │00 ├───┤12 │13 │14 │    │50 │51 │52 ├───┤44 │
    ├───┤11 ├───┼───┼───┤    ├───┼───┼───┤53 ├───┤
    │10 ├───┤22 │23 │24 │    │60 │61 │62 ├───┤54 │
    ├───┤21 ├───┼───┼───┤    ├───┼───┼───┤63 ├───┤
    │20 ├───┤32 │33 │34 │    │70 │71 │72 ├───┤64 │
    └───┘31 └───┴───┴───┘    └───┴───┴───┘73 └───┘

*/

#define LAYOUT_blackflat_4x12( \
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    L30, _LR, L32, L33, L34, R30, R31, R32, _RR, R34 \
    ) \
    { \
        { L00, L01, L02, L03, L04 }, \
        { L10, L11, L12, L13, L14 }, \
        { L20, L21, L22, L23, L24 }, \
        { L30, _LR, L32, L33, L34 }, \
        { R00, R01, R02, R03, R04 }, \
        { R10, R11, R12, R13, R14 }, \
        { R20, R21, R22, R23, R24 }, \
        { R30, R31, R32, _RR, R34 } \
    }


#define LAYOUT_blackbowl_4x12( \
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    L30, _LR, L32, L33, L34, R30, R31, R32, _RR, R34  \
    ) \
    { \
        { R30, R20, R10, R00 }, \
        { R31, R21, R11, R01 }, \
        { R32, R22, R12, R02 }, \
        { xxx, R23, R13, R03 }, \
        { R34, R24, R14, R04 }, \
        { L30, L20, L10, L00 }, \
        { xxx, L21, L11, L01 }, \
        { L32, L22, L12, L02 }, \
        { L33, L23, L13, L03 }, \
        { L34, L24, L14, L04 } \
    }

/*
    RedTilt: outermost "thumb" keys are in topmost row
    Ring finger thumbkeys (32/73) missing in matrix!

    ┌───┬───┐   ┌───┬───┬───┐    ┌───┬───┬───┐   ┌───┬───┐
    │30*│31*├───┤03 │04 │05 │    │40 │41 │42 ├───┤74*│75*│
    ├───┼───┤02 ├───┼───┼───┤    ├───┼───┼───┤43 ├───┼───┤
    │00 │01 ├───┤13 │14 │15 │    │50 │51 │52 ├───┤44 │45 │
    ├───┼───┤12 ├───┼───┼───┤    ├───┼───┼───┤53 ├───┼───┤
    │10 │11 ├───┤23 │24 │25 │    │60 │61 │62 ├───┤54 │55 │
    ├───┼───┤22 ├───┼───┼───┤    ├───┼───┼───┤63 ├───┼───┤
    │20 │21 ├───┤33 │34 │35 │    │70 │71 │72 ├───┤64 │65 │
    └───┴───┘   └───┴───┴───┘    └───┴───┴───┘   └───┴───┘

*/

// add two pinky columns
#define LAYOUT_redtilt_4x12( \
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    L30, _LR, L32, L33, L34, R30, R31, R32, _RR, R34, \
    L0P, L1P, L2P, L3P, \
    R0P, R1P, R2P, R3P  \
    ) \
    { \
        { L0P, L00, L01, L02, L03, L04 }, \
        { L1P, L10, L11, L12, L13, L14 }, \
        { L2P, L20, L21, L22, L23, L24 }, \
        { L3P, L30, _LR, L32, L33, L34 }, \
        { R00, R01, R02, R03, R04, R0P }, \
        { R10, R11, R12, R13, R14, R1P }, \
        { R20, R21, R22, R23, R24, R2P }, \
        { R30, R31, R32, _RR, R34, R3P } \
    }


#define LAYOUT_sweep_3x5_2( \
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    _3a, _3b, _3c, L33, L34, R30, R31, _3x, _3y, _3z \
    ) \
    { \
        { L00, L01, L02, L03, L04 }, \
        { L10, L11, L12, L13, L14 }, \
        { L20, L21, L22, L23, L24 }, \
        {                L33, L34 }, \
        { R00, R01, R02, R03, R04 }, \
        { R10, R11, R12, R13, R14 }, \
        { R20, R21, R22, R23, R24 }, \
        { R30, R31                } \
    }

#define LAYOUT_crowboard_3x5_3( \
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    _3a, _3b, L32, L33, L34, R30, R31, R32, _3y, _3z \
    ) \
    { \
        { L00, L01, L02, L03, L04,     R00, R01, R02, R03, R04 }, \
        { L10, L11, L12, L13, L14,     R10, R11, R12, R13, R14 }, \
        { L20, L21, L22, L23, L24,     R20, R21, R22, R23, R24 }, \
        { xxx, xxx, L32, L33, L34,     R30, R31, R32           } \
    }


#define LAYOUT_chocofi_3x5_3(\
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, R20, R21, R22, R23, R24, \
    _3a, _3b, L32, L33, L34, R30, R31, R32, _3y, _3z \
    ) \
    { \
        { xxx, L00, L01, L02, L03, L04 }, \
        { xxx, L10, L11, L12, L13, L14 }, \
        { xxx, L20, L21, L22, L23, L24 }, \
        { xxx, xxx, xxx, L32, L33, L34 }, \
        { xxx, R04, R03, R02, R01, R00 }, \
        { xxx, R14, R13, R12, R11, R10 }, \
        { xxx, R24, R23, R22, R21, R20 }, \
        { xxx, xxx, xxx, R32, R31, R30 } \
    }

// clang-format on
