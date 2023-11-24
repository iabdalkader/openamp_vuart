/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */
#include <string.h>
#include "ringbuf.h"

void ringbuf_init(ringbuf_t *buf) {
    memset(buf, 0, sizeof(*buf));
}

int ringbuf_empty(ringbuf_t *buf) {
    return (buf->head == buf->tail);
}

int ringbuf_put(ringbuf_t *buf, uint8_t c) {
    if ((buf->tail + 1) % RINGBUF_BUF_SIZE == buf->head) {
        // Buffer is full
        return -1;
    }

    buf->data[buf->tail] = c;
    buf->tail = (buf->tail + 1) % RINGBUF_BUF_SIZE;
    return 0;
}

int ringbuf_get(ringbuf_t *buf) {
    uint8_t c;
    if (buf->head == buf->tail) {
        // Buffer is empty
        return -1;
    }

    c = buf->data[buf->head];
    buf->head = (buf->head + 1) % RINGBUF_BUF_SIZE;
    return c;
}
