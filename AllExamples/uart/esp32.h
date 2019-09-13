/*
 * esp32.h
 *
 *  Created on: Apr 20, 2019
 *      Author: Caleb
 */
#include "uart.h"

#ifndef ESP32_H_
#define ESP32_H_

void init_ESP32(void);
void ESP32_transmit_4byte_Array(uint8_t data[4]);
void ESP32_sendData(void);

#endif /* ESP32_H_ */
