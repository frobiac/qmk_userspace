// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

/// Implements an automatic temporary remapping of few convenient keys
/// to easy to reach mouse buttons when the pointing device is in use.
///
/// Currently, only PS2 trackpoints are supported.
/// Timeouts and thresholds for activation and continued usage can be configured.
/// These must be adusted according to the sensitivity and threshold set for
/// the trackpoint in use.
///
/// Feature is selected only by setting CUSTOM_AUTO_MBTN_ENABLE externally, so no
/// further checking is required in this file.
///
/// Additionally, a complete switch to the '_MOUSE' layer can be performed,
/// but is usually not necessary nor recommended
///
/// @TODO: Configure keys? Depend on layout for now!

#include "frobiac.h" // include userspace for layouts
#include "timer.h"
#include "keycode.h" // IS_KEY()

// needed for VIAL which only supports IS_KEY
#if !defined(IS_BASIC_KEYCODE)
#    ifndef IS_KEY
#        error IS_KEY is not defined, needed for IS_BASIC_KEYCODE redefinition
#    endif
#    define IS_BASIC_KEYCODE IS_KEY
#endif

/// Control duration of mouse layer activation after no more mouse envents are received.
/// Reset to 0 to terminate further handling early.
static uint16_t auto_l_timer = 0;

// @TODO: Make configurable e.g. for Hypernano where trackpoint is separated, and dedicated extra keys could be used.
// @TODO: Convert to matrix positions to be layout agnostic! E.g. col,row: L= 2,4, R=2,5 N=3,5
/// Which keys to remap to mouse buttons 1..x
static uint16_t mbtn_remaps[] = {KC_R, KC_N, KC_L};

#ifndef CUSTOM_AUTO_MBTN_TIMEOUT_MS
#    define CUSTOM_AUTO_MBTN_TIMEOUT_MS 2000
#endif

// NOTE: heavily depends on trackpoint sensitivity and speed settings
#ifndef CUSTOM_AUTO_MBTN_REFRESH_TH
#    define CUSTOM_AUTO_MBTN_REFRESH_TH 5
#endif
#ifndef CUSTOM_AUTO_MBTN_INITIAL_TH
#    define CUSTOM_AUTO_MBTN_INITIAL_TH 14
#endif

// if defined, auto mouse button feature will stop on any non-modifier key being pressed.
// This should help against accidental activation of the feature when sensitivity of the trackpoint
// is too high. Note that only basic keycodes are used, for combined keys use the abort key define below.
#define AMB_LEAVE_ON_OTHER_KEYS 1
// Key to leave automatic remapping immediately. Useful when e.g. KC_ESC is chosen, but placed on a layer toggle mod tap.
#define CUSTOM_AUTO_MBTN_ABORT_KEY _NAVESC
// Key for manual mouse layer activation, to stop our automatic timeout
#define CUSTOM_AUTO_MBTN_OVERRIDE_KEY _MOUS_X

/// simple wrapper around layer_[on|off](_MOUSE) to need only single #define for toggling feature
void maybe_set_mouse_layer(bool on) {
#if defined(CUSTOM_AUTO_MBTN_FULL)
    if (on)
        layer_on(_MOUSE);
    else
        layer_off(_MOUSE);
#endif
}

// Layer switching on trackpoint usage based on Charybdis code
// also see feature_pointing_devices.md (but no PS2?) and POINTING_DEVICE_ENABLE
// also see tap_hold.md
// also see pierce/keymaps/durken1 for usage with custom keycode
//
// @TODO Also keep timer active while mouse layer keys are used
// @TODO Or don't use entire layer switching logic, but only remap 3 buttons next to TP temporarily?
void ps2_mouse_moved_autombtn(report_mouse_t *mouse_report) {
    // Make initial threshold higher to prevent accidental activation, and then just keep resetting timer on smaller thresholds.
    // Has to be tweaked in coordination with trackpoint sensitivity and inertia settings.
    uint16_t delta = abs(mouse_report->x) + abs(mouse_report->y);
    if ((auto_l_timer != 0 && delta > CUSTOM_AUTO_MBTN_REFRESH_TH) || delta > CUSTOM_AUTO_MBTN_INITIAL_TH) {
        if (auto_l_timer == 0) {
            maybe_set_mouse_layer(true);
        }
        auto_l_timer = timer_read();
    }
}

void matrix_scan_autombtn(void) {
    if (auto_l_timer != 0 && TIMER_DIFF_16(timer_read(), auto_l_timer) >= CUSTOM_AUTO_MBTN_TIMEOUT_MS) {
        maybe_set_mouse_layer(false);
        auto_l_timer = 0;
    }
}

// Store toggled mouse button replacement bit for latter reset
static uint8_t mbtn3 = 0;

/// If auto-layer timer is running, map presses of 'from' to 'to'
/// On release, check if any 'to's still need to be released in replacement of 'from' release
/// Could also refactor to derive 'bit' and 't' from common mouse button index, and use a map of 'from:to' pairs.
bool map_three_buttons(uint16_t from, uint16_t to, uint8_t bit, bool is_pressed) {
    if (is_pressed) {
        if (auto_l_timer == 0) {
            return true; // no remapping
        }
        auto_l_timer = timer_read();
        unregister_code(from);
        register_code(to);
        mbtn3 |= (1 << bit);
        return false;
    } else { // still a pressed remapped state not released available?
        if ((mbtn3 & (1 << bit)) != 0) {
            mbtn3 ^= (1 << bit);
            unregister_code(to);
            return false;
        }
        return true;
    }
}

/// Check if mouse timer is active, and map configured keys to mouse buttons.
bool process_record_automousebutton(uint16_t keycode, keyrecord_t *record) {
    // xprintf("KL: kc: %04X, col: %02u, row: %02u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    for (size_t i = 0; i < sizeof(mbtn_remaps) / sizeof(mbtn_remaps[0]); ++i) {
        if (keycode == mbtn_remaps[i]) {
            if (!map_three_buttons(keycode, KC_BTN1 + i, i, record->event.pressed)) {
                return false;
            }
        }
    }

#ifdef AMB_LEAVE_ON_OTHER_KEYS
    // Optional keys used in conjuction with mouse: Modifiers: Shift/Control, maybe.
    // Note that this does *not* cover modtaps or other non-standard basic keys.
    if (IS_BASIC_KEYCODE(keycode)) {
        auto_l_timer = 0;
        return true;
    }
#endif

    switch (keycode) {
        case CUSTOM_AUTO_MBTN_OVERRIDE_KEY:
            // When the key to activate mouse layer manually is held,
            // disable the automatic timeout that would otherwise disable it.
            if (!record->tap.count && record->event.pressed) {
                auto_l_timer = 0;
            }
            return true; // Return true for normal processing of tap keycode
            break;

        case CUSTOM_AUTO_MBTN_ABORT_KEY:
            // disable automatic mouse layer selection immediately on _NAVESC
            if (record->event.pressed) {
                if (auto_l_timer != 0) {
                    auto_l_timer = 0;
                    maybe_set_mouse_layer(false);
                    // only swallow on ESC, keep possibility to switch layer by holding
                    if (record->tap.count) {
                        return false;
                    }
                    return true; // normal handling of possible tap_hold layer toggle
                }
            }
            break;
    }

    return true;
}
