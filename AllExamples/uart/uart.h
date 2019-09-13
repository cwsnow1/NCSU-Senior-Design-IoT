/*
 * uart.h
 *
 *  Created on: Apr 20, 2019
 *      Author: Caleb
 */

#include "driverlib.h"

#ifndef UART_H_
#define UART_H_

#define BUFFER_SIZE (16)

void UART_initPorts(void);
void UART_init(uint16_t base);
void EUSCI_A_UART_transmitArray(uint16_t base, uint8_t data[], int length);
void EUSCI_A_UART_transmitString(uint16_t base, char string[]);

#endif /* UART_H_ */
