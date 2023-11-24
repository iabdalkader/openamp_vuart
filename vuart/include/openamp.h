/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __OPENAMP_H__
#define __OPENAMP_H__
#include "openamp/open_amp.h"
#include "openamp/remoteproc.h"

typedef struct openamp_rsc_table {
    unsigned int version;
    unsigned int num;
    unsigned int reserved[2];
    #if OPENAMP_TRACE_ENABLE
    unsigned int offset[2];
    #else
    unsigned int offset[1];
    #endif
    struct fw_rsc_vdev vdev;
    struct fw_rsc_vdev_vring vring0;
    struct fw_rsc_vdev_vring vring1;
    #if OPENAMP_TRACE_ENABLE
    struct fw_rsc_trace trace;
    #endif
} openamp_rsc_table_t;

typedef struct rpmsg_endpoint endpoint_t;
typedef int (*ep_callback_t) (endpoint_t *ept, void *data, size_t len, uint32_t src, void *priv);

int openamp_init(void);
void openamp_deinit(void);
int openamp_ep_init(endpoint_t *ep, uint32_t src, uint32_t dst, const char *name, ep_callback_t cb, void *priv);
void openamp_ep_deinit(endpoint_t *ep);
int openamp_ep_send(endpoint_t *ep, uint32_t src, uint32_t dst, void *data, size_t len, uint32_t timeout);
#endif // __OPENAMP_H__
