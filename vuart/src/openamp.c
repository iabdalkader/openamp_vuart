/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include "metal/alloc.h"
#include "metal/errno.h"
#include "metal/io.h"
#include "metal/sys.h"
#include "metal/device.h"
#include "metal/utilities.h"
#include "metal/metal_port.h"

#include "openamp/open_amp.h"
#include "openamp/remoteproc.h"
#include "openamp/remoteproc_loader.h"

#include "openamp.h"
#include "openamp_port.h"
#include "systick.h"
#include "common.h"

typedef struct _virtio_dev_t {
    struct rpmsg_virtio_device rvdev;
    struct rpmsg_virtio_shm_pool shm_pool;
} virtio_dev_t;

static virtio_dev_t virtio_device;

static struct metal_device shm_device = {
    .name = METAL_SHM_NAME,
    // The number of IO regions is fixed and must match the number and
    // layout of the remote processor's IO regions. The first region is
    // used for the vring shared memory, and the second one is used for
    // the shared resource table.
    .num_regions = METAL_MAX_DEVICE_REGIONS,
    .regions = { { 0 } },
    .node = { NULL },
    .irq_num = 0,
    .irq_info = NULL
};

static metal_phys_addr_t shm_physmap[] = { 0 };

int openamp_init(void) {
    struct metal_device *device;
    struct metal_init_params metal_params = METAL_INIT_DEFAULTS;

    // The host initializes the shared resource table.
    openamp_rsc_table_t *rsc_table = METAL_RSC_ADDR;

    // Initialize libmetal.
    metal_init(&metal_params);

    if (metal_register_generic_device(&shm_device) != 0) {
        fatal_error("Failed to register virtio device");
    }

    if (metal_device_open("generic", shm_device.name, &device) != 0) {
        fatal_error("Failed to open shared virtio device");
    }

    // Initialize shared memory IO region.
    metal_io_init(&device->regions[0], (void *) METAL_SHM_ADDR, (void *) shm_physmap, METAL_SHM_SIZE, -1U, 0, NULL);
    struct metal_io_region *shm_io = metal_device_io_region(device, 0);
    if (shm_io == NULL) {
        fatal_error("Failed to initialize device io region");
    }

    // Initialize resource table IO region.
    metal_io_init(&device->regions[1], (void *) rsc_table, (void *) rsc_table, sizeof(*rsc_table), -1U, 0, NULL);
    struct metal_io_region *rsc_io = metal_device_io_region(device, 1);
    if (rsc_io == NULL) {
        fatal_error("Failed to initialize device io region");
    }

    // Create virtio device.
    struct virtio_device *vdev = rproc_virtio_create_vdev(RPMSG_REMOTE, VIRTIO_DEV_ID,
                                                          &rsc_table->vdev, rsc_io, NULL, metal_rproc_notify, NULL);
    if (vdev == NULL) {
        fatal_error("Failed to create virtio device");
    }

    // Initialize vrings.
    struct fw_rsc_vdev_vring *vring_rsc = &rsc_table->vring0;
    for (int i = 0; i < VRING_COUNT; i++, vring_rsc++) {
        if (rproc_virtio_init_vring(vdev, vring_rsc->notifyid, vring_rsc->notifyid,
                                    (void *) vring_rsc->da, shm_io, vring_rsc->num, vring_rsc->align) != 0) {
            fatal_error("Failed to initialize vrings");
        }
    }

    // The remote processor detects that the virtio device is ready by polling
    // the status field in the resource table.
    rpmsg_virtio_init_shm_pool(&virtio_device.shm_pool, (void *) VRING_BUFF_ADDR, (size_t) VRING_BUFF_SIZE);
    rpmsg_init_vdev(&virtio_device.rvdev, vdev, NULL, shm_io, &virtio_device.shm_pool);
    return 0;
}

void openamp_deinit(void) {
    rpmsg_deinit_vdev(&virtio_device.rvdev);
    metal_finish();
}

int openamp_ep_init(endpoint_t *ep, uint32_t src, uint32_t dst, const char *name, ep_callback_t cb, void *priv) {
    //ep->priv = priv;
    if (rpmsg_create_ept(ep, &virtio_device.rvdev.rdev, name, src, dst, cb, NULL) != 0) {
        fatal_error("Failed to create RPMsg endpoint");
    }
    return 0;
}

void openamp_ep_deinit(endpoint_t *ep) {
    rpmsg_destroy_ept(ep);
}

int openamp_ep_send(endpoint_t *ep, uint32_t src, uint32_t dst, void *data, size_t len, uint32_t timeout) {
    if (!is_rpmsg_ept_ready(ep)) {
        return -1;
    }

    int bytes = 0;
    for (uint32_t start = systick_millis(); ; systick_sleep(10)) {
        bytes = rpmsg_send_offchannel_raw(ep, src, dst, data, len, false);
        if (bytes > 0) {
            break;
        }
        if (timeout > 0 && (systick_millis() - start > timeout)) {
            return -1;
        }
    }
    return 0;
}

void metal_rproc_notified() {
    rproc_virtio_notified(virtio_device.rvdev.vdev, VRING_NOTIFY_ID);
}
