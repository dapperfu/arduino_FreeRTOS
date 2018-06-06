#!/bin/sh

watchmedo shell-command --pattern "*.c;*.h;*.ino" --command "make"
