/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __MIMXRT_OPENAMP_PORT_H__
#define __MIMXRT_OPENAMP_PORT_H__

#define VIRTIO_DEV_ID           0xFF
#define VIRTIO_DEV_FEATURES     (1 << VIRTIO_RPMSG_F_NS)

#define VRING0_ID               0   // VRING0 ID (master to remote) fixed to 0 for linux compatibility
#define VRING1_ID               1   // VRING1 ID (remote to master) fixed to 1 for linux compatibility
#define VRING_NOTIFY_ID         VRING1_ID

#define VRING_COUNT             2
#define VRING_ALIGNMENT         32
// Note the number of buffers must be a power of 2
#define VRING_NUM_BUFFS         64

// The following config should be enough for about 128 descriptors.
// See lib/include/openamp/virtio_ring.h for the layout of vrings
// and vring_size() to calculate the vring size.
#define VRING_RX_ADDR           (METAL_SHM_ADDR)
#define VRING_TX_ADDR           (METAL_SHM_ADDR + 0x1000)
#define VRING_BUFF_ADDR         (METAL_SHM_ADDR + 0x2000)
#define VRING_BUFF_SIZE         (METAL_SHM_SIZE - 0x2000)

#endif // __MIMXRT_OPENAMP_PORT_H__
