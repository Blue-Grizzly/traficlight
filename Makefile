MCU = atmega328p
F_CPU = 16000000UL
BAUD = 115200
PORT ?= /dev/ttyUSB0

SRC = ./trafficlight.c
OBJ = build/trafficlight.elf
HEX = build/trafficlight.hex

all: compile upload clean

compile: $(SRC)
	@echo "Compiling..."
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Wall -Os -o $(OBJ) $(SRC)
	avr-objcopy -O ihex -R .eeprom $(OBJ) $(HEX)
	@echo "Compiled."

upload: $(HEX)
	@echo "Uploading..."
	avrdude -v -p$(MCU) -c arduino -P$(PORT) -b$(BAUD) -D -Uflash:w:$(HEX):i
	@echo "Uploaded."

clean:
	@echo "Cleaning..."
	rm -f $(OBJ) $(HEX)
	@echo "Cleaned."

.PHONY: all compile upload clean