# This file is part of the openamp_vurat example.
#
# Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
# This work is licensed under the MIT license, see the file LICENSE for details.
#
# libmetal Makefile
SRCS = $(addprefix src/,\
	device.c \
	dma.c \
	init.c \
	io.c \
	irq.c \
	log.c \
	shmem.c \
	softirq.c \
	version.c \
	device.c \
	system/generic/condition.c \
	system/generic/device.c \
	system/generic/io.c \
	system/generic/irq.c \
	system/generic/shmem.c \
	system/generic/time.c \
    )

OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
OBJ_DIRS = $(sort $(dir $(OBJS)))

all: | $(OBJ_DIRS) $(OBJS)
$(OBJ_DIRS):
	$(MKDIR) -p $@

$(BUILD_DIR)/%.o : %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o : %.s
	$(ECHO) "AS $<"
	$(AS) $(AFLAGS) $< -o $@

-include $(OBJS:%.o=%.d)
