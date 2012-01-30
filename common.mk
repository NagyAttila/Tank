# settings
ARDUINO_DIR=/home/ptr/build/arduino-1.0

# path variables
ARDUINO_CORE_DIR=$(ARDUINO_DIR)/hardware/arduino/cores/arduino
ARDUINO_LCD_DIR=$(ARDUINO_DIR)/libraries/LiquidCrystal

VPATH=$(ARDUINO_CORE_DIR):$(ARDUINO_LCD_DIR):$(SRC_DIR)

# tools
CXX=avr-g++
CC=avr-gcc
AR=avr-ar
OCP=avr-objcopy

# compilation flags
CFLAGS=-c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=100
CXXFLAGS=$(CFLAGS) -fno-exceptions
INCFLAGS=\
	-I$(ARDUINO_CORE_DIR) \
	-I$(ARDUINO_DIR)/hardware/arduino/variants/standard \
	-I$(ARDUINO_LCD_DIR) \
	-I$(ARDUINO_LCD_DIR)/utility

# core lib
CORE_OBJS=\
	WInterrupts.o wiring_shift.o wiring_analog.o wiring_digital.o wiring.o wiring_pulse.o \
	new.o CDC.o Print.o USBCore.o IPAddress.o Tone.o WMath.o HardwareSerial.o Stream.o WString.o main.o HID.o


# implicit rules
.c.o:
	$(CC) $(CFLAGS) $(INCFLAGS) $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $< -o $@

%.elf:
	$(CC) -Os -Wl,--gc-sections -mmcu=atmega328p -o $@ $^ -lm

%.a:
	$(AR) rcs $@ $^

%.eep: %.elf
	$(OCP) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@

%.hex: %.elf
	$(OCP) -O ihex -R .eeprom $< $@ 

# other targets
clean:
	rm -f *.o *.a *.elf *.eep *.hex

install: $(PROGRAM).hex
	avrdude -v -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -D -Uflash:w:$(PROGRAM).hex:i

core.a : $(CORE_OBJS)

# dependencies
build: $(PROGRAM).eep $(PROGRAM).hex


