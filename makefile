# settings
PROGRAM=tank

SRC_DIR=src

OBJS=\
	stepper.o \
	tank.o \
	infra.o

#	stepper.o \
	microstepper.o

# dependencies
all: build

$(PROGRAM).elf : $(OBJS) core.a

include common.mk

