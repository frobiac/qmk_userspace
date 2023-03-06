// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

#pragma once

#if defined(PS2_MOUSE_ENABLE) && defined(PS2_RESET_PIN)

// Also copied in individual keyboards by request on initial PR
void tp_reset(void);

#endif
