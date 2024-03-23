/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <stdint.h>
#include "vuart.h"

#define RPMSG_SERVICE_NAME              "vuart-channel"

static int rpmsg_ep_callback(struct rpmsg_endpoint *ep, void *data, size_t len, uint32_t src, void *priv) {
    vuart_t *vuart = metal_container_of(ep, struct _vuart, ep);
    for (size_t i=0; i<len; i++) {
        ringbuf_put(&vuart->rxbuf, ((uint8_t *) data)[i]);
    }
    if (vuart->callback != NULL) {
        vuart->callback(vuart);
    }
    return 0;
}

int vuart_init(vuart_t *vuart, vuart_callback_t callback, void *userdata) {
    vuart->callback = callback;
    vuart->userdata = userdata;
    ringbuf_init(&vuart->rxbuf);
    if (openamp_ep_init(&vuart->ep, RPMSG_ADDR_ANY, RPMSG_ADDR_ANY, RPMSG_SERVICE_NAME, rpmsg_ep_callback, NULL) != 0) {
        return -1;
    }
    return 0;
}

int vuart_deinit(vuart_t *vuart) {
    openamp_ep_deinit(&vuart->ep);
    return 0;
}

int vuart_any(vuart_t *vuart) {
    return !ringbuf_empty(&vuart->rxbuf);
}

int vuart_read(vuart_t *vuart, uint8_t *data, size_t size) {
    uint32_t i = 0;
    while (!ringbuf_empty(&vuart->rxbuf) && size--) {
        data[i++] = ringbuf_get(&vuart->rxbuf);
    }
    return i;
}

int vuart_write(vuart_t *vuart, uint8_t *data, size_t size) {
    endpoint_t *ep = &vuart->ep;
    if (openamp_ep_send(ep, ep->addr, ep->dest_addr, data, size, 0) != 0) {
        return -1;
    }
    return 0;
}
