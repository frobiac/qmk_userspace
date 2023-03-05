// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

#pragma once

// cannot be included due to preprocessor conflicts? "quantum.h" instead?
#include QMK_KEYBOARD_H

// automatically included with -km frobiac, even if keymap.c does not #include "frobiac.h"
// #warning FROBIAC.H INCLUDED

// Including layout.h here instead of in config.h works for '-km frobiac' compiles
// But *not* for JSON compile.
// ??? when include here, plenty of 'unkown opcode' void ... errors
// #include "layout.h"

#include "trackpoint.h"
#include "automousebutton.h"
