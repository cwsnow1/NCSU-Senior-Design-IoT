/*
 * sht35.c
 *
 *  Created on: Apr 8, 2019
 *      Author: caleb
 */

#include "sht35.h"

uint8_t sht35data[6];

void SHT35_sendCommand(uint8_t MSB, uint8_t LSB) {
	// Send command.
	EUSCI_B_I2C_masterSendMultiByteStart(EUSCI_B2_BASE, MSB);
	EUSCI_B_I2C_masterSendMultiByteFinish(EUSCI_B2_BASE, LSB);
	// Delay until transmission completes
	while (EUSCI_B_I2C_isBusBusy(EUSCI_B2_BASE))
		;
}

float SHT35_getTemp(uint8_t data[]) {
	/*
	uint16_t temp_raw = (data[0] << 8) + data[1];
	float temp_raw_f = (float) temp_raw;
	float temp_f = 315.0 * (temp_raw_f / 65535.0) - 49.0;
	return temp_f;
	*/
	return 1.3;
}

float SHT35_getHumidity(uint8_t data[]) {
	uint16_t humidity_raw = (data[3] << 8) + data[4];
	float humidity_f = 100.0f * ((float) humidity_raw / 65535.0f);
	return humidity_f;
}
