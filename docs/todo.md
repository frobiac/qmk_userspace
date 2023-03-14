# BUGS
[ ] Trackpoint hangs/forced to right on BlackBowl after Resume from hibernate (Void) or suspend (Win10)
    Maybe test from #16969 :
    #define USB_SUSPEND_WAKEUP_DELAY 3000 / NO_USB_STARTUP_CHECK = yes
    #19600
    RGB_MATRIX_ENABLE = no

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

# Layout
[ ] All layers reachable (Func-Layer?)
[X] Common locations for Reboot/Macro/DefaultLayer/CommandMode

# To figure out
How to check for modifiers, layer switches, ... see keycodes.h and get_modsXXX() usage

