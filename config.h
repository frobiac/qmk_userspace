// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

#pragma once

// QMK variables and defines shall be put here, in conjunction with
// configuration in `rules.mk`

// This file is automatically included with
// * builds using -km frobiac, but *only* if keymap.c *does* #include "frobiac.h"
//   (and without including config.h explicitely there)
// * *AND* during JSON compile

// Including `layout.h` here works for both JSON and '-km frobiac' compiles, but
// needs an "#ifndef __ASSEMBLER__" guard around german keymap inclusion and layer enum
#include "layout.h"
