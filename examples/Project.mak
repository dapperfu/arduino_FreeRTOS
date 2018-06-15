# Build Settings
ARCHITECTURE ?= avr
BOARD_TAG ?= nano
BOARD_SUB ?= atmega328

# Environment Settings.
ARDUINO_DIR?=$(realpath ../../arduino)
ARDUINO_LIB_PATH=$(realpath ${ARDUINO_DIR}/hardware/arduino/avr/libraries)
USER_LIB_PATH?=$(realpath ../../libraries)



-include libs.mak
include ../../arduino_make/Arduino.mk

# Format Code
.PHONY: format
format:
	clang-format-6.0 -i -style=file *.ino
	clang-format-6.0 -i -style=file *.h
	clang-format-6.0 -i -style=file *.c

low_pass: low_pass.c
	clang-6.0 -o ${@} ${^}

