
.pio/build/uno/firmware.hex: src/PinToggle.cpp
	${MAKE} format
	platformio run

.PHONY: upload
upload: .pio/build/uno/firmware.hex
	avrdude -v -V -p m328p -c arduino -P /dev/ttyUSB0 -D -U flash:w:${^}

.PHONY: format
format:
	clang-format -i src/*

.PHONY: clean
clean:
	rm -rf .pio
