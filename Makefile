
ROOT=$(shell pwd)
PROJ_NAME = main

###################################################
# Toolchain
###################################################
TC          = arm-none-eabi
#CC          = $(TC)-gcc
# Projects containing C++ must be compiled with a C++ compiler
CC          = $(TC)-g++
CPP         = $(TC)-g++
AS          = $(TC)-as
AR          = $(TC)-ar
LD          = $(TC)-ld
OBJCOPY     = $(TC)-objcopy
OBJDUMP     = $(TC)-objdump
SIZE        = $(TC)-size
GDB         = $(TC)-gdb
###################################################

USER_SRCS   := $(wildcard src/*.c src/*/*.c src/*/*/*.c)
LIB_SRCS    := $(wildcard lib/DisplayCore/*.cpp)
LIB_SRCS    := $(wildcard lib/BD663474/*.cpp)
LIB_SRCS    := $(wildcard lib/XPT2046/*.cpp)

LIBS        = -lm -lc -lgcc

INCLUDES    += -I include
INCLUDES    += -I lib/DisplayCore
INCLUDES    += -I lib/BD663474
INCLUDES    += -I lib/XPT2046

OPTIMIZE    = -Og
DEBUG       = -g -Wall

# Required for compatibility between Print.h and DisplayCore
DEFINES     += -DARDUINO=100

# Target platform
include Makefile-F446RE.mk

CFLAGS += $(DEFINES) $(INCLUDES) -Wno-main

CPPFLAGS += $(DEFINES) $(INCLUDES)

# Object files
STARTUP_OBJ := $(STARTUP_SRC:.s=.o)
LIB_OBJS    := $(LIB_SRCS:.c=.o)
LIB_OBJS    := $(LIB_OBJS:.cpp=.o)
USER_OBJS   := $(USER_SRCS:.c=.o)

# Colorify compiler output
ifdef COLOR
CC_COLORS = sed -e "s/\(warning:\)/\x1b[1;33m&\x1b[0m/" -e "s/\(error:\)/\x1b[91m&\x1b[0m/"
CPP_COLORS = $(CC_COLORS)
LD_COLORS = sed -e "s/:[0-9]*:\([ 0-9a-zA-Z_\`\']*\)/:\x1b[1;91m\1\x1b[0m/"
endif

# OpenOCD
OPENOCD = openocd
OPENOCD_DEBUGGER = interface/stlink-v2-1.cfg
OPENOCD_ARGS = -f $(OPENOCD_DEBUGGER) -f $(OPENOCD_TARGET)

###################################################
# Targets
###################################################

all: sdk $(PROJ_NAME).bin $(PROJ_NAME).lst info

sdk:
#	ifeq ($(wildcard lib/STM32Cube_FW_F3_V1.8.0/*),)
#	cd lib; ./download-libs.sh
#	endif

ifndef LD_COLORS
$(PROJ_NAME).elf: $(STARTUP_OBJ) $(LIB_OBJS) $(USER_OBJS)
	@rm -f $@
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo $@
else
$(PROJ_NAME).elf: $(STARTUP_OBJ) $(LIB_OBJS) $(USER_OBJS)
	@rm -f $@
	$(CC) $^ $(LDFLAGS) -o $@ 2>&1 | $(LD_COLORS)
	@echo $@
endif

ifndef CC_COLORS
.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@
	@echo $@
else
.c.o:
	$(CC) $(CFLAGS) -c $^ -o $@ 2>&1 | $(CC_COLORS)
	@echo $@
endif

ifndef CPP_COLORS
.cpp.o:
	$(CPP) $(CPPFLAGS) -c $^ -o $@ 2>&1
else
.cpp.o:
	$(CPP) $(CPPFLAGS) -c $^ -o $@ 2>&1 | $(CPP_COLORS)
endif

.s.o:
	$(CC) $(ASFLAGS) -c $^ -o $@
	@#2>&1 | $(CC_COLORS)
	@echo $@


$(PROJ_NAME).bin: $(PROJ_NAME).elf
	@$(OBJCOPY) $< -O binary $@
	@echo $@

$(PROJ_NAME).lst: $(PROJ_NAME).elf
	@$(OBJDUMP) -h -S $< > $@
	@echo $@

# Memory Usage Info
info: $(PROJ_NAME).elf
	@$(SIZE) --format=berkeley $<

# Remove all SDK-unspecific sources files
semiclean:
	rm -f $(USER_OBJS)
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst

clean: semiclean
	rm -f $(STARTUP_OBJ)
	rm -f $(LIB_OBJS)

openocd:
	$(OPENOCD) $(OPENOCD_ARGS)

.PHONY: debug
debug: $(PROJ_NAME).elf
	$(GDB) $< -ex="target remote localhost:3333" -ex="load" -ex="monitor reset halt"

flash: $(PROJ_NAME).elf
	$(OPENOCD) $(OPENOCD_ARGS) -c "program $(PROJ_NAME).elf verify reset exit"

terminal:
	screen /dev/ttyNucleo 460800

