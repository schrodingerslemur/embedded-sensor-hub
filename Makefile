CC=avr-gcc
MCU=atmega328p
F_CPU=16000000UL
CFLAGS=-std=c11 -Wall -Os -DF_CPU=$(F_CPU)
OBJ=main.o scheduler.o sensor.o uart.o ringbuf.o cli.o

all: sensorhub.elf

%.o: %.c
	$(CC) $(CFLAGS) -mmcu=$(MCU) -c $< -o $@

sensorhub.elf: $(OBJ)
	$(CC) $(CFLAGS) -mmcu=$(MCU) $(OBJ) -o sensorhub.elf

flash: sensorhub.elf
	avrdude -c arduino -p $(MCU) -P /dev/ttyACM0 -b115200 -U flash:w:sensorhub.elf:e

clean:
	rm -f *.o sensorhub.elf