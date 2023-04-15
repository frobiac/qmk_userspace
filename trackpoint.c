// Copyright 2023 @frobiac
// SPDX-License-Identifier: MIT

// @TODO: ScrollBtn speed lower

#include "frobiac.h"

#ifdef PS2_MOUSE_ENABLE

#    include "trackpoint.h"
#    include "ps2_mouse.h"
#    include "ps2.h"
#    include "gpio.h"

#    if defined(PS2_RESET_PIN)
/**
 *  If the recommended reset circuitry is not attached to trackpoints reset line,
 *  it is possible do simulate it with a regular GPIO.
 *
 *  To be called just before `ps2_host_init()`. The necessary 500ms delay is included.
 *
 *  Hook up in keyboard_init() just before ps2_mouse_init(), e.g. keyboard_pre_init_user()
 *
 *  See ZMK PR #1751 for 600ms low and then High again?!
 *  https://github.com/zmkfirmware/zmk/blob/98a7ed3633fcfbb28b2b119d7c8d2a50dc7e5b86/app/src/mouse/mouse_ps2.c
 */
void tp_reset(void) {
    setPinOutput(PS2_RESET_PIN);
    writePinHigh(PS2_RESET_PIN);
    wait_us(150); // PS2_DELAY
    writePinLow(PS2_RESET_PIN);
    wait_ms(600); // wait for power up
    writePinHigh(PS2_RESET_PIN);
    // now ready to call ps2_host_init()
}
#    endif // PS2_RESET_PIN

// @TODO: Remaining params of original firmware: drag, PTS
// define TP_PTS_TOGGLE 0x2C // defconfig with bit 0 set
#    define TP_COMMAND 0xE2
#    define TP_WRITE_MEM 0x81
#    define TP_SENS 0x4A       // 0 - 1.99 [0x80 == 1.0]
#    define TP_INERTIA 0x4D    // 0-255 [0x06       ]
#    define TP_SPEED 0x60      // see EngSpec [0x06 == low res 2x accel ]
#    define TP_PTS_THRESH 0x5C // Minimum value for a Z-axis press
#    define TP_DEFCONFIG 0x2C  // O:|PTS|RES|2BT|~X |~Y |~Z |X-Y|FHT]:7

// convenience function to set trackpoint registers
void tp_ram_write(uint8_t addr, uint8_t val) {
    // @TODO prefer PS2_MOUSE_SEND()?
    ps2_host_send(TP_COMMAND);
    ps2_host_send(TP_WRITE_MEM);
    ps2_host_send(addr);
    ps2_host_send(val);
}

// More responsive trackpoint settings.
// May also ned PS2 resolution / multiplier adjustements
//
// Note: These effect calculations in 'ps2_mouse_moved_user()' :
//       SE=224 SP=224 : delta up to 20 on slightest touch, 60 on violent janks (with cap attached)
//       SE=128 SP=160 : delta up to 12 on slightest touch, 35 on violent janks (without cap attached)
//       SE=160 SP=208 : better
// Original Hypernano settings
//       SE=224 SP=224 TH=16
void ps2_mouse_init_trackpoint(void) {
    // sensitivity, speed, ...
    tp_ram_write(TP_SENS, 0xA0);
    tp_ram_write(TP_SPEED, 0xD0);
    // tp_ram_write(TP_INERTIA, 0x06);
    // tp_ram_write(TP_PTS_THRESH, 0x10);

    // axes and PtS config
    // tp_ram_write(TP_DEFCONFIG, 0x01); // E2 47 2C 01 ?

    // setup PressToSroll by enabling PTS, setting button masks and increasing threshold
    // tp_ram_write(0x41, 0xff); // external pointing?
    // tp_ram_write(0x42, 0xff);
}

void keyboard_pre_init_trackpoint(void) {
#    if defined(PS2_RESET_PIN)
    tp_reset();
#    endif
}

bool process_record_trackpoint(uint16_t keycode, keyrecord_t *record) {
#    if defined(PS2_RESET_PIN)
    // @TODO Test if trackpoint reset fixes drift error
    if (keycode == TP_RESET) {
        tp_reset();
        return false;
    }
#    endif
    return true;
}

#endif // PS2_MOUSE_ENABLE
