/* ringbuf.c */
#include "ringbuf.h"

typedef struct {
    uint8_t *buf;
    int head, tail, size;
} ring_t;

static ring_t r;

void ring_init(uint8_t *buffer, int sz) {
    r.buf = buffer;
    r.size = sz;
    r.head = r.tail = 0;
}

int ring_push(uint8_t v) {
    int next = (r.head + 1) % r.size;
    if (next == r.tail)
        return 0;
    r.buf[r.head] = v;
    r.head = next;
    return 1;
}

int ring_pop(uint8_t *v) {
    if (r.head == r.tail)
        return 0;
    *v = r.buf[r.tail];
    r.tail = (r.tail + 1) % r.size;
    return 1;
}