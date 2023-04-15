// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

#pragma once

#if defined(PS2_MOUSE_ENABLE)

void ps2_mouse_init_trackpoint(void);
void keyboard_pre_init_trackpoint(void);
bool process_record_trackpoint(uint16_t keycode, keyrecord_t *record);

#endif
