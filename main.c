// Code for testing the SBUS library

#include <stdio.h>
#include "pico/stdlib.h"
#include <SBUSReader/SBUS.h>

int main() {
	stdio_init_all();

	init_sbus();

	while (true) {
		printf("SBUS: %d\t%d\t%d\t%d\n", sbus.channels[0], sbus.channels[1], sbus.channels[2], sbus.channels[3]);
		printf("Failsafe: %d\n", sbus.failsafe);
		sleep_ms(100);
	}

	return 0;
}