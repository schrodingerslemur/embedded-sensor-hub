#include "sensor.h"
#include "uart.h"
#include <stdio.h>

static int fake_val = 0;

void sensor_init(void) {
    fake_val = 0;
}

int sensor_read(void) {
    fake_val = (fake_val + 7) % 1024;
    return fake_val;
}

void sensor_poll_task(void) {
    int v = sensor_read();
    char out[32];
    sprintf(out, "S:%d\n", v);
    uart_write_str(out);
}