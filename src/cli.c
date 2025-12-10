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