#include <SBUSReader/SBUS.h>

static struct sbus_data sbus;

static char sbus_buffer[SBUS_FRAME_SIZE];
static int sbus_buffer_index = 0;

void on_uart_rx() {
	while (uart_is_readable(SBUS_UART_ID)) {
		uint8_t ch = uart_getc(SBUS_UART_ID);

		if (sbus_buffer_index == 0 && ch != SBUS_FRAME_START) {
			continue;
		}

		sbus_buffer[sbus_buffer_index++] = ch;

		// Check if the buffer is full
		if (sbus_buffer_index == SBUS_FRAME_SIZE) {
			// Check if the last byte is the end of the frame
			if (sbus_buffer[SBUS_FRAME_SIZE - 1] == SBUS_FRAME_END) {
				// Decode the SBUS frame
				sbus.channels[0] = (sbus_buffer[1] | sbus_buffer[2] << 8) & 0x07FF;
				sbus.channels[1] = (sbus_buffer[2] >> 3 | sbus_buffer[3] << 5) & 0x07FF;
				sbus.channels[2] = (sbus_buffer[3] >> 6 | sbus_buffer[4] << 2 | sbus_buffer[5] << 10) & 0x07FF;
				sbus.channels[3] = (sbus_buffer[5] >> 1 | sbus_buffer[6] << 7) & 0x07FF;
				sbus.channels[4] = (sbus_buffer[6] >> 4 | sbus_buffer[7] << 4) & 0x07FF;
				sbus.channels[5] = (sbus_buffer[7] >> 7 | sbus_buffer[8] << 1 | sbus_buffer[9] << 9) & 0x07FF;
				sbus.channels[6] = (sbus_buffer[9] >> 2 | sbus_buffer[10] << 6) & 0x07FF;
				sbus.channels[7] = (sbus_buffer[10] >> 5 | sbus_buffer[11] << 3) & 0x07FF;
				sbus.channels[8] = (sbus_buffer[12] | sbus_buffer[13] << 8) & 0x07FF;
				sbus.channels[9] = (sbus_buffer[13] >> 3 | sbus_buffer[14] << 5) & 0x07FF;
				sbus.channels[10] = (sbus_buffer[14] >> 6 | sbus_buffer[15] << 2 | sbus_buffer[16] << 10) & 0x07FF;
				sbus.channels[11] = (sbus_buffer[16] >> 1 | sbus_buffer[17] << 7) & 0x07FF;
				sbus.channels[12] = (sbus_buffer[17] >> 4 | sbus_buffer[18] << 4) & 0x07FF;
				sbus.channels[13] = (sbus_buffer[18] >> 7 | sbus_buffer[19] << 1 | sbus_buffer[20] << 9) & 0x07FF;
				sbus.channels[14] = (sbus_buffer[20] >> 2 | sbus_buffer[21] << 6) & 0x07FF;
				sbus.channels[15] = (sbus_buffer[21] >> 5 | sbus_buffer[22] << 3) & 0x07FF;

				sbus.ch17 = (sbus_buffer[23] & 0x80) != 0;
				sbus.ch18 = (sbus_buffer[23] & 0x40) != 0;
				sbus.frame_lost = (sbus_buffer[23] & 0x20) != 0;
				sbus.failsafe = (sbus_buffer[23] & 0x10) != 0;
				
				sbus.last_update = time_us_32();

				// Reset the buffer index
				sbus_buffer_index = 0;

				// Print the SBUS data if SBUS_USB_DEBUG is enabled
				#if SBUS_USB_DEBUG
				printf("SBUS: ");
				for (int i = 0; i < 16; i++) {
					printf("%d ", sbus.channels[i]);
				}
				printf("%d %d %d %d\n", sbus.ch17, sbus.ch18, sbus.frame_lost, sbus.failsafe);
				#endif
			}
		}
	}
}

void init_sbus() {
	// Initialize UART and invert the RX pin
	uart_init(SBUS_UART_ID, SBUS_BAUD_RATE);

	// Set TX and RX pins
	gpio_set_function(SBUS_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(SBUS_RX_PIN, GPIO_FUNC_UART);
	gpio_set_inover(SBUS_RX_PIN, GPIO_OVERRIDE_INVERT);

	uart_set_hw_flow(SBUS_UART_ID, false, false);
	uart_set_format(SBUS_UART_ID, SBUS_DATA_BITS, SBUS_STOP_BITS, UART_PARITY_NONE);
	uart_set_fifo_enabled(SBUS_UART_ID, false);

	int UART_IRQ = SBUS_UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

	// Enable UART interrupt
	irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
	irq_set_enabled(UART_IRQ, true);
	uart_set_irq_enables(SBUS_UART_ID, true, false);
}

void read_sbus(struct sbus_data *sbus_data) {
	// Copy the SBUS data to the provided struct
	memcpy(sbus_data, &sbus, sizeof(struct sbus_data));
}
