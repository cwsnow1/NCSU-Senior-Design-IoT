/*
 * uart.c
 *
 *  Created on: Apr 20, 2019
 *      Author: Caleb
 */

#include "uart.h"

uint8_t UART_buffer[BUFFER_SIZE];
bool client_connected;

void UART_initPorts(void) {
	// Configure UART pins
	//Set P2.0 and P2.1 as Secondary Module Function Input.
	/*

	 * Select Port 2d
	 * Set Pin 0, 1 to input Primary Module Function, (UCA3TXD/UCA3SIMO, UCA3RXD/UCA3SOMI).
	 */
	GPIO_setAsPeripheralModuleFunctionInputPin(
	GPIO_PORT_P2,
	GPIO_PIN0 + GPIO_PIN1,
	GPIO_SECONDARY_MODULE_FUNCTION);

	//Set P6.0 and P6.1 as Primary Module Function Input.
	/*

	 * Select Port 6d
	 * Set Pin 0, 1 to input Primary Module Function, (UCA3TXD/UCA3SIMO, UCA3RXD/UCA3SOMI).
	 */
	GPIO_setAsPeripheralModuleFunctionInputPin(
	GPIO_PORT_P6,
	GPIO_PIN0 + GPIO_PIN1,
	GPIO_PRIMARY_MODULE_FUNCTION);
}

void UART_init(uint16_t base) {
	// Configure UART
	EUSCI_A_UART_initParam param = { 0 };
	param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
	param.clockPrescalar = 4;
	param.firstModReg = 5;
	param.secondModReg = 0x55;
	param.parity = EUSCI_A_UART_NO_PARITY;
	param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
	param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
	param.uartMode = EUSCI_A_UART_MODE;
	param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;

	if (STATUS_FAIL == EUSCI_A_UART_init(base, &param)) {
		return;
	}

	EUSCI_A_UART_enable(base);

	EUSCI_A_UART_clearInterrupt(base,
	EUSCI_A_UART_RECEIVE_INTERRUPT);

	// Enable USCI_Ax RX interrupt
	EUSCI_A_UART_enableInterrupt(base,
	EUSCI_A_UART_RECEIVE_INTERRUPT);                     // Enable interrupt

}

//******************************************************************************
//
//This is the USCI_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A0_VECTOR)))
#endif
void USCI_A0_ISR(void) {
	uint8_t RXData;
	switch (__even_in_range(UCA0IV, USCI_UART_UCTXCPTIFG)) {
	case USCI_NONE:
		break;
	case USCI_UART_UCRXIFG:
		RXData = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
		// echo back to UCA0
		//EUSCI_A_UART_transmitData(EUSCI_A0_BASE, RXData);
		EUSCI_A_UART_transmitData(EUSCI_A3_BASE, RXData);
		break;
	case USCI_UART_UCTXIFG:
		break;
	case USCI_UART_UCSTTIFG:
		break;
	case USCI_UART_UCTXCPTIFG:
		break;
	}
}

//******************************************************************************
//
//This is the USCI_A3 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A3_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_A0_VECTOR)))
#endif
void USCI_A3_ISR(void) {
	uint8_t RXData;
	switch (__even_in_range(UCA3IV, USCI_UART_UCTXCPTIFG)) {
	case USCI_NONE:
		break;
	case USCI_UART_UCRXIFG:
		RXData = EUSCI_A_UART_receiveData(EUSCI_A3_BASE);
		EUSCI_A_UART_transmitData(EUSCI_A0_BASE, RXData);
		break;
	case USCI_UART_UCTXIFG:
		break;
	case USCI_UART_UCSTTIFG:
		break;
	case USCI_UART_UCTXCPTIFG:
		break;
	}
}

void EUSCI_A_UART_transmitString(uint16_t base, char string[]) {
	int i = 0;
	while (string[i] != '\0') {
		EUSCI_A_UART_transmitData(EUSCI_A0_BASE, string[i]);
		EUSCI_A_UART_transmitData(base, string[i++]);
	}
}

void EUSCI_A_UART_transmitArray(uint16_t base, uint8_t data[], int length) {
	int i;
	for (i = 0; i < length; i++) {
		EUSCI_A_UART_transmitData(EUSCI_A0_BASE, data[i]);
		EUSCI_A_UART_transmitData(base, data[i]);
	}
}

