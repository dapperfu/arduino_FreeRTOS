# Config

# Environments to setup for this project
# Available options: python arduino
ENVS:=arduino python

## make_sandwich includes
# https://github.com/jed-frey/make_sandwich
include .mk_inc/env.mk

SUBMAKE=$(wildcard */Makefile)

examples: ${SUBMAKE}

.PHONY: ${SUBMAKE}
${SUBMAKE}:
	-@${MAKE} -C $(@D)
