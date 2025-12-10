#pragma once

void sensor_init(void);
int sensor_read(void);
void sensor_poll_task(void);

/* uart.c */
#include "uart.h"
#include <avr/io.h>

void uart_init(unsigned long baud) {
    unsigned short ubrr = F_CPU/16/baud - 1;
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0A = (unsigned char)ubrr;
    UCSR0B = (1<<TXEN0) | (1<<RXEN0);
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void uart_write(char c) {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = c;
}

void uart_write_str(const char *s) {
    while (*s) uart_write(*s++);
}

char uart_read(void) {
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

int uart_available(void) {
    return (UCSR0A & (1<<RXC0));
}