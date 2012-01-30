# settings
PROGRAM=tank

SRC_DIR=src

OBJS=\
	tank.o \

#	stepper.o \
	microstepper.o

# dependencies
all: build

$(PROGRAM).elf : $(OBJS) LiquidCrystal.o core.a

include common.mk

