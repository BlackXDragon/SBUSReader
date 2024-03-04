// Raspberry Pi Pico library to read SBUS as a UART signal

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include <string.h>

#if !defined(SBUS_h)
#define SBUS_h

#ifndef SBUS_USB_DEBUG
#define SBUS_USB_DEBUG 0
#endif

#define SBUS_UART_ID uart0
#define SBUS_DATA_BITS 8
#define SBUS_STOP_BITS 2

#define SBUS_TX_PIN 0
#define SBUS_RX_PIN 1

#if !defined(FAST_SBUS)
#define FAST_SBUS 0
#endif

#if FAST_SBUS
#define SBUS_BAUD_RATE 200000
#else
#define SBUS_BAUD_RATE 100000
#endif

#define SBUS_FRAME_SIZE 25
#define SBUS_FRAME_START 0x0F
#define SBUS_FRAME_END 0x00

struct sbus_data {
	uint16_t channels[16];
	bool ch17;
	bool ch18;
	bool frame_lost;
	bool failsafe;
};

void on_uart_rx();

void init_sbus();

void read_sbus(struct sbus_data *data);

#endif // SBUS_h