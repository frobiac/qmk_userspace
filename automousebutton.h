// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

#pragma once

void ps2_mouse_moved_autombtn(report_mouse_t *mouse_report);
void matrix_scan_autombtn(void);
bool process_record_automousebutton(uint16_t keycode, keyrecord_t *record);
