# Raspberry Pi Python3 script to read serial output from the SBUS reader and runs even when disconnected waiting for a connection

import time
import serial

SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 921600

ser = None

try:
	while True:
		if not ser:
			try:
				ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
				print('Connected to serial port')
			except serial.SerialException:
				print('Waiting for serial port')
				time.sleep(1)
				continue
		else:
			try:
				print(ser.readline())
			except serial.SerialException:
				print('Disconnected from serial port')
				ser = None
except KeyboardInterrupt:
	if ser:
		ser.close()
	print('Exiting')
