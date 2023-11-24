# This file is part of the openamp_vurat example.
# Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
# This work is licensed under the MIT license, see the file LICENSE for details.
#
# Top level Makefile

# Set verbosity
ifeq ($(V), 1)
Q =
else
Q = @
MAKEFLAGS += --silent
endif

CC      = $(Q)arm-none-eabi-gcc
CXX     = $(Q)arm-none-eabi-g++
AS      = $(Q)arm-none-eabi-as
LD      = $(Q)arm-none-eabi-ld
AR      = $(Q)arm-none-eabi-ar
RM      = $(Q)rm
CPP     = $(Q)arm-none-eabi-cpp
SIZE    = $(Q)arm-none-eabi-size
STRIP   = $(Q)arm-none-eabi-strip -s
OBJCOPY = $(Q)arm-none-eabi-objcopy
OBJDUMP = $(Q)arm-none-eabi-objdump
PYTHON  = $(Q)python3
MKDIR   = $(Q)mkdir
ECHO    = $(Q)@echo
MAKE    = $(Q)make
CAT     = $(Q)cat

PORT ?= stm32

# Directories
TOP_DIR=$(shell pwd)
BUILD_DIR=$(TOP_DIR)/build
FW_DIR=$(BUILD_DIR)/bin
HAL_DIR=hal
CMSIS_DIR=hal/cmsis
VUART_DIR=vuart
OPENAMP_DIR=openamp
LIBMETAL_DIR=metal
PORTABLE_DIR = portable

# Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -Og -ggdb3
else
CFLAGS += -O2 -ggdb3 -DNDEBUG
endif

# Enable debug printf
ifeq ($(DEBUG_PRINTF), 1)
CFLAGS += -DDEBUG_PRINTF
endif

# Enable stack protection
ifeq ($(STACK_PROTECTOR), 1)
CFLAGS += -fstack-protector-all -DSTACK_PROTECTOR
endif

# Include the port Makefile.
include $(PORTABLE_DIR)/$(PORT)/port_config.mk

size:
	$(SIZE) --format=SysV $(FW_DIR)/$(FIRMWARE).elf

clean:
	$(RM) -fr $(BUILD_DIR)
