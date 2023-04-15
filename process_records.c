// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

#include "frobiac.h"
// #include "process_records.h"

extern uint32_t keepalive_timer;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

#ifdef PS2_MOUSE_ENABLE
extern bool process_record_trackpoint(uint16_t keycode, keyrecord_t *record);
#endif

#ifdef CUSTOM_AUTO_MBTN_ENABLE
extern bool process_record_automousebutton(uint16_t keycode, keyrecord_t *record);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    keepalive_timer = timer_read32();

    return process_record_keymap(keycode, record) &&
#ifdef PS2_MOUSE_ENABLE
           process_record_trackpoint(keycode, record) &&
#endif
#ifdef CUSTOM_AUTO_MBTN_ENABLE
           process_record_automousebutton(keycode, record) &&
#endif
           true;
}
