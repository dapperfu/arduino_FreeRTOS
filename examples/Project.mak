# Build Settings
ARCHITECTURE ?= avr
BOARD_TAG ?= uno
BOARD_SUB ?= atmega328

# Environment Settings.
ARDUINO_DIR?=$(realpath ../../arduino)
ARDUINO_LIB_PATH=$(realpath ${ARDUINO_DIR}/hardware/arduino/avr/libraries)
USER_LIB_PATH?=$(realpath ../../libraries)

-include libs.mak
include ../../arduino_make/Arduino.mk
