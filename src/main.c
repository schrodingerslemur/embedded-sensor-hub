#include "scheduler.h"
#include "sensor.h"
#include "uart.h"
#include "cli.h"

int main(void) {
    uart_init(115200);
    sensor_init();
    scheduler_init();
    cli_init();

    scheduler_add_task(sensor_poll_task, 10);
    scheduler_add_task(cli_task, 1);

    while (1) {
        scheduler_run();
    }
}