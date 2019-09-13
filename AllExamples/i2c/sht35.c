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
