# This file is part of the openamp_vurat example.
# Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
# This work is licensed under the MIT license, see the file LICENSE for details.

FIRMWARE = vuart
LDSCRIPT = mimxrt
SYSTEM   = system_MIMXRT1176_cm4
STARTUP  = startup_MIMXRT1176_cm4
IMXRT_HAL_DIR = $(HAL_DIR)/mimxrt/MIMXRT1176

# Compiler Flags
CFLAGS += -std=gnu99 \
          -Wall \
          -Werror \
          -fdata-sections \
          -ffunction-sections \
          -mcpu=cortex-m4 \
          -mfpu=fpv4-sp-d16 \
          -mfloat-abi=hard \
          -mthumb \
          -Wdouble-promotion \

CFLAGS += -DCPU_MIMXRT1176DVMAA_cm4\
          -DCMSIS_MCU_H='<MIMXRT1176_cm4.h>' \
          -D__START=main \
          -D__STARTUP_CLEAR_BSS \
          -D__USE_SHMEM
          # __STARTUP_INIT_DATA

CFLAGS += -DMETAL_INTERNAL \
          -DNO_ATOMIC_64_SUPPORT \
          -DVIRTIO_DEVICE_ONLY \
          -DMETAL_MAX_DEVICE_REGIONS=2 \
          -DRPMSG_BUFFER_SIZE=512 \
          -DOPENAMP_TRACE_ENABLE=1

CFLAGS += -I. \
          -I$(TOP_DIR)/$(CMSIS_DIR)/include/ \
          -I$(TOP_DIR)/$(CMSIS_DIR)/include/mimxrt \
          -I$(TOP_DIR)/$(IMXRT_HAL_DIR)/ \
          -I$(TOP_DIR)/$(IMXRT_HAL_DIR)/drivers/ \
          -I$(TOP_DIR)/$(IMXRT_HAL_DIR)/drivers/cm4 \
          -I$(TOP_DIR)/$(OPENAMP_DIR)/ \
          -I$(TOP_DIR)/$(OPENAMP_DIR)/lib/include/ \
          -I$(TOP_DIR)/$(LIBMETAL_DIR)/include/ \
          -I$(TOP_DIR)/$(VUART_DIR)/include \
          -I$(TOP_DIR)/$(PORTABLE_DIR)/$(PORT) \
          -I$(TOP_DIR)/$(PORTABLE_DIR)/$(PORT)/metal \
          -I$(TOP_DIR)/$(PORTABLE_DIR)/$(PORT)/openamp \

# Linker Flags
LDFLAGS = -mcpu=cortex-m4 \
          -mfpu=fpv4-sp-d16 \
          -mfloat-abi=hard \
          -mthumb \
          -Wl,--gc-sections\
          -Wl,-T$(BUILD_DIR)/$(LDSCRIPT).lds \
          --specs=nosys.specs \
          -static \
          -Wl,--no-warn-rwx-segment\

# Libraries
LIBS =

SRCS += $(addprefix $(OPENAMP_DIR)/lib/,\
	rpmsg/rpmsg.c \
	rpmsg/rpmsg_virtio.c \
	virtio/virtio.c \
	virtio/virtqueue.c \
	virtio_mmio/virtio_mmio_drv.c \
	remoteproc/remoteproc.c \
	remoteproc/remoteproc_virtio.c \
	remoteproc/rsc_table_parser.c \
	)

BUILD_DIRS += $(BUILD_DIR)
BUILD_DIRS += $(FW_DIR)
BUILD_DIRS += $(addprefix $(BUILD_DIR)/, $(sort $(dir $(SRCS))))

# Firmware objects
FIRM_OBJ += $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(CMSIS_DIR)/src/mimxrt/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(IMXRT_HAL_DIR)/drivers/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(IMXRT_HAL_DIR)/drivers/cm4/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(LIBMETAL_DIR)/src/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(LIBMETAL_DIR)/src/system/generic/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(PORTABLE_DIR)/$(PORT)/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(PORTABLE_DIR)/$(PORT)/metal/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(PORTABLE_DIR)/$(PORT)/openamp/*.o)
FIRM_OBJ += $(wildcard $(BUILD_DIR)/$(VUART_DIR)/src/*.o)

#Export Variables
export Q
export CC
export AS
export LD
export AR
export SIZE
export OBJCOPY
export OBJDUMP
export MKDIR
export ECHO
export CFLAGS
export LDFLAGS
export TOP_DIR
export BUILD_DIR
export SYSTEM
export STARTUP
export PORT

all: $(FIRMWARE)

$(BUILD_DIRS):
	$(ECHO) "mkdir $@"
	$(MKDIR) -p $@

$(BUILD_DIR)/%.o : %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o : %.s
	$(ECHO) "AS $<"
	$(AS) $(AFLAGS) $< -o $@

$(FIRM_OBJ): | $(BUILD_DIRS)

FIRMWARE_OBJS: $(FIRM_OBJ)
	$(MAKE)  -C $(CMSIS_DIR)     BUILD_DIR=$(BUILD_DIR)/$(CMSIS_DIR)     CFLAGS="$(CFLAGS) -fno-strict-aliasing -MMD"
	$(MAKE)  -C $(IMXRT_HAL_DIR) BUILD_DIR=$(BUILD_DIR)/$(IMXRT_HAL_DIR) CFLAGS="$(CFLAGS) -MMD"
	$(MAKE)  -C $(LIBMETAL_DIR)  BUILD_DIR=$(BUILD_DIR)/$(LIBMETAL_DIR)  CFLAGS="$(CFLAGS) -MMD"
	$(MAKE)  -C $(PORTABLE_DIR)  BUILD_DIR=$(BUILD_DIR)/$(PORTABLE_DIR)  CFLAGS="$(CFLAGS) -MMD"
	$(MAKE)  -C $(VUART_DIR)     BUILD_DIR=$(BUILD_DIR)/$(VUART_DIR)     CFLAGS="$(CFLAGS) -MMD"

# This target generates the firmware image.
$(FIRMWARE): FIRMWARE_OBJS
	$(CPP) -P -E $(PORTABLE_DIR)/$(PORT)/$(LDSCRIPT).ld.S > $(BUILD_DIR)/$(LDSCRIPT).lds
	$(CC) $(LDFLAGS) $(FIRM_OBJ) -o $(FW_DIR)/$(FIRMWARE)_debug.elf $(LIBS)
	$(STRIP) $(FW_DIR)/$(FIRMWARE)_debug.elf -o $(FW_DIR)/$(FIRMWARE).elf
	$(OBJCOPY) -Obinary $(FW_DIR)/$(FIRMWARE)_debug.elf $(FW_DIR)/$(FIRMWARE).bin
	$(SIZE) $(FW_DIR)/$(FIRMWARE).elf
