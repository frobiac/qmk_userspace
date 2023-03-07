# Common features
# COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
BOOTMAGIC_ENABLE = no
# if disabled, leads to xprintf errors in blackflat json compile
# but only if not using german keymap workaround?
CONSOLE_ENABLE = no


ifeq ($(strip $(MCU)), atmega32u4)
	LTO_ENABLE = yes
endif

SRC += frobiac.c \
	   process_records.c \

# Trackpoint boards:
# Default is to enable PS2_MOUSE_ENABLE here, but may be set to 'no' in keymaps' rules.mk to override
# Support for older PS2 mode selection (as in VIAL) is also done here
ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), frobiac/hypernano frobiac/blackflat frobiac/blackbowl frobiac/redtilt))
	# Only teensies
	BOOTLOADER = halfkay

	PS2_MOUSE_ENABLE ?= yes
	ifeq ($(strip $(PS2_MOUSE_ENABLE)), yes)
		# PS2_ENABLE = yes # implicitely enabeled by PS2_MOUSE_ENABLE
		ifeq ($(strip $(KEYBOARD)), $(filter $(KEYBOARD), frobiac/blackbowl))
			PS2_DRIVER = usart
			PS2_USE_USART = yes # compatibility with older VIAL QMK
		else
			PS2_DRIVER = busywait
			PS2_USE_BUSYWAIT = yes
		endif

		SRC += trackpoint.c
		CUSTOM_AUTO_MBTN_ENABLE = yes
	endif
endif

# @TODO How about other possible pointing devices?
CUSTOM_AUTO_MBTN_ENABLE ?= no
ifeq ($(strip $(CUSTOM_AUTO_MBTN_ENABLE)), yes)
    SRC += $(USER_PATH)/automousebutton.c
    OPT_DEFS += -DCUSTOM_AUTO_MBTN_ENABLE
endif

