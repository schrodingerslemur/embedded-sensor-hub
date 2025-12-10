#include "scheduler.h"

#define MAX_TASKS 8
static task_t tasks[MAX_TASKS];
static int task_count = 0;

void scheduler_init(void) {
    task_count = 0;
}

void scheduler_add_task(void (*func)(void), int interval) {
    tasks[task_count].func = func;
    tasks[task_count].interval = interval;
    tasks[task_count].counter = interval;
    task_count++;
}

void scheduler_run(void) {
    for (int i = 0; i < task_count; i++) {
        if (--tasks[i].counter <= 0) {
            tasks[i].func();
            tasks[i].counter = tasks[i].interval;
        }
    }
}
