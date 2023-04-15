# BUGS
[ ] Trackpoint hangs/forced to right on BlackBowl after Resume from hibernate (Void) or suspend (Win10)
    Maybe test from #16969 :
    #define USB_SUSPEND_WAKEUP_DELAY 3000 / NO_USB_STARTUP_CHECK = yes
    #19600
    RGB_MATRIX_ENABLE = no

## fixed
[X] Trackpoint selection with AutoMouseButtons not working, only clicks.

# General
[ ] Check if VIAL can also be compiled via JSON instead of keyboard/frobiac/*/keymaps/vial
[ ] Add install instructions from scratch rafaelromao/keyboards and gerryhernandez/gkey

# QMK features and settings
[ ] LED where available
[ ] HN: TP sensitivity of HyperNano higher: Does not have an extension stick
[ ] HN: Mouse buttons on middle unused buttons
[ ] XOR
[ ] Ferris/Sweep
[ ] Crowboard
[ ] Scroll/Caps/.. Lock leds for signalling to OS (waybar)
[X] Sync with VIAL
[X] Store userspace in personal github
[X] Convert all to JSON

# VIAL
[#] VIAL_ENABLE to check QMK and VIAL in userspace (e.g XorShift functions not available)

# Layout
[ ] All layers reachable (Func-Layer?)
[X] Common locations for Reboot/Macro/DefaultLayer/CommandMode

# To figure out
How to check for modifiers, layer switches, ... see keycodes.h and get_modsXXX() usage


# Board specific

## RedTilt

[X] Trackpoint in VIAL: OK

Working in AdNW v0.9.7-353-g1c31c1f-D-2021-01-17
    EE[15] 0005: 0C 0000 Mouse=1-1 AL=0
    TP: Sens:  28/128 SP= 97 TH=249
    PTS=0 X=1 Y=1 (18)
