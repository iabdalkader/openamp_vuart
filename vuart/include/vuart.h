/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#ifndef __VUART_H__
#define __VUART_H__

#include "openamp.h"
#include "ringbuf.h"

typedef struct _vuart vuart_t;
typedef void (*vuart_callback_t) (vuart_t *vuart);

typedef struct _vuart {
    ringbuf_t rxbuf;
    void *userdata;
    vuart_callback_t callback;
    struct rpmsg_endpoint ep;
} vuart_t;

int vuart_init(vuart_t *vuart, vuart_callback_t callback, void *userdata);
int vuart_deinit(vuart_t *vuart);
int vuart_any(vuart_t *vuart);
int vuart_read(vuart_t *vuart, uint8_t *data, size_t size);
int vuart_write(vuart_t *vuart, uint8_t *data, size_t size);
#endif // __VUART_H__
