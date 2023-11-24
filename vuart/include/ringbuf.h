/*
 * This file is part of the OpenAMP Virtual UART Example.
 *
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * Simple Ring Buffer implementation.
 */
#ifndef __RINGBUF_H__
#define __RINGBUF_H__
#include <stdint.h>
#define RINGBUF_BUF_SIZE    (4096)

typedef struct ringbuf {
    volatile uint32_t head;
    volatile uint32_t tail;
    uint8_t data[RINGBUF_BUF_SIZE];
} ringbuf_t;

void ringbuf_init(ringbuf_t *buf);
int ringbuf_empty(ringbuf_t *buf);
int ringbuf_put(ringbuf_t *buf, uint8_t c);
int ringbuf_get(ringbuf_t *buf);
#endif /* __RINGBUF_H__ */
