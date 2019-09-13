/*
 * adc.h
 *
 *  Created on: Apr 21, 2019
 *      Author: Caleb
 */
#include "driverlib.h"

#ifndef ADC_H_
#define ADC_H_

//#define ADC_A4
#ifdef ADC_A4
#define ADC
#endif

void init_ADC12B(void);
void init_ADC12B_memoryBuffer(uint8_t memoryBufferControlIndex,
		uint8_t inputSourceSelect, uint16_t IFG_mask, uint16_t IE_mask);
void ADC_initPorts(void);

#endif /* ADC_H_ */
