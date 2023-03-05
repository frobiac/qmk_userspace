// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

// @TODO userspace_config ?
//
#include "frobiac.h"

static uint32_t g_ka_timeout_ms = (uint32_t)(5) * 60 * 1000;
uint32_t        keepalive_timer;

void housekeeping_task_user(void) {
    if (timer_elapsed32(keepalive_timer) > g_ka_timeout_ms) {
        keepalive_timer = timer_read32();
        SEND_STRING_DELAY(SS_TAP(X_AUDIO_VOL_UP), 50);
        SEND_STRING_DELAY(SS_TAP(X_AUDIO_VOL_DOWN), 50);
    }
}

__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
#ifdef CUSTOM_AUTO_MBTN_ENABLE
    matrix_scan_autombtn();
#endif
    matrix_scan_keymap();
}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
#ifdef CUSTOM_AUTO_MBTN_ENABLE
    ps2_mouse_moved_autombtn(mouse_report);
#endif
}

__attribute__((weak)) void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
#ifdef PS2_MOUSE_ENABLE
    keyboard_pre_init_trackpoint();
#endif
    keyboard_pre_init_keymap();
}

// Check if this would be a could place to fix uncontrollable movement after suspend,
// should it occur again.
__attribute__((weak)) void suspend_power_down_keymap(void) {}

__attribute__((weak)) void suspend_wakeup_init_keymap(void) {}

void suspend_wakeup_init_user(void) {
    // ps2_mouse_init();
    suspend_wakeup_init_keymap();
}
