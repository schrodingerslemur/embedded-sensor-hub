#pragma once

void uart_init(unsigned long baud);
void uart_write(char c);
void uart_write_str(const char *s);
char uart_read(void);
int uart_available(void);

/* cli.c */
#include "cli.h"
#include "uart.h"
#include "sensor.h"
#include <string.h>

static char buf[32];
static int idx = 0;

void cli_init(void) {
    idx = 0;
}

void cli_task(void) {
    if (!uart_available()) return;
    char c = uart_read();
    if (c == '\n') {
        buf[idx] = '\0';
        if (strcmp(buf, "read") == 0) {
            int v = sensor_read();
            char out[32];
            sprintf(out, "Now:%d\n", v);
            uart_write_str(out);
        }
        idx = 0;
    } else {
        if (idx < sizeof(buf)-1) buf[idx++] = c;
    }
}