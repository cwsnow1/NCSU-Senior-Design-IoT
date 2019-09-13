/*
 * adc.c
 *
 *  Created on: Apr 21, 2019
 *      Author: Caleb
 */
#include "adc.h"

uint16_t ADC_A4_value;

void ADC_initPorts(void) {
	//Set P1.4 as Ternary Module Function Output.
	/*

	 * Select Port 1
	 * Set Pin 1 to output Ternary Module Function, (A1, C1, VREF+, VeREF+).
	 */
	GPIO_setAsPeripheralModuleFunctionOutputPin(
	GPIO_PORT_P1,
	GPIO_PIN4,
	GPIO_TERNARY_MODULE_FUNCTION);
}

void init_ADC12B() {

	//Initialize the ADC12B Module
	/*
	 * Base address of ADC12B Module
	 * Use internal ADC12B bit as sample/hold signal to start conversion
	 * USE MODOSC 5MHZ Digital Oscillator as clock source
	 * Use default clock divider/pre-divider of 1
	 * Not use internal channel
	 */
	ADC12_B_initParam initParam = { 0 };
	initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;
	initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
	initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
	initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
	initParam.internalChannelMap = ADC12_B_NOINTCH;
	ADC12_B_init(ADC12_B_BASE, &initParam);

	//Enable the ADC12B module
	ADC12_B_enable(ADC12_B_BASE);

	/*
	 * Base address of ADC12B Module
	 * For memory buffers 0-7 sample/hold for 64 clock cycles
	 * For memory buffers 8-15 sample/hold for 4 clock cycles (default)
	 * Disable Multiple Sampling
	 */
	ADC12_B_setupSamplingTimer(ADC12_B_BASE, ADC12_B_CYCLEHOLD_16_CYCLES,
	ADC12_B_CYCLEHOLD_4_CYCLES,
	ADC12_B_MULTIPLESAMPLESDISABLE);

}

void init_ADC12B_memoryBuffer(uint8_t memoryBufferControlIndex,
		uint8_t inputSourceSelect, uint16_t IFG_mask, uint16_t IE_mask) {

	//Configure Memory Buffer
	/*
	 * Base address of the ADC12B Module
	 * Configure memory buffer 0
	 * Map input A1 to memory buffer 0
	 * Vref+ = AVcc
	 * Vref- = AVss
	 * Memory buffer 0 is not the end of a sequence
	 */
	ADC12_B_configureMemoryParam configureMemoryParam = { 0 };
	configureMemoryParam.memoryBufferControlIndex = memoryBufferControlIndex;
	configureMemoryParam.inputSourceSelect = inputSourceSelect;
	configureMemoryParam.refVoltageSourceSelect =
	ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
	configureMemoryParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
	configureMemoryParam.windowComparatorSelect =
	ADC12_B_WINDOW_COMPARATOR_DISABLE;
	configureMemoryParam.differentialModeSelect =
	ADC12_B_DIFFERENTIAL_MODE_DISABLE;
	ADC12_B_configureMemory(ADC12_B_BASE, &configureMemoryParam);

	ADC12_B_clearInterrupt(ADC12_B_BASE, 0, IFG_mask);

	//Enable memory buffer 0 interrupt
	ADC12_B_enableInterrupt(ADC12_B_BASE, IE_mask, 0, 0);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC12_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(ADC12_VECTOR)))
#endif
void ADC12_ISR(void) {

	switch (__even_in_range(ADC12IV, 12)) {
	case 0:
		break;                         // Vector  0:  No interrupt
	case 2:
		break;                         // Vector  2:  ADC12BMEMx Overflow
	case 4:
		break;                         // Vector  4:  Conversion time overflow
	case 6:
		break;                         // Vector  6:  ADC12BHI
	case 8:
		break;                         // Vector  8:  ADC12BLO
	case 10:
		break;                         // Vector 10:  ADC12BIN
	case 12:                                // Vector 12:  ADC12BMEM0 Interrupt
		ADC_A4_value = ADC12_B_getResults(ADC12_B_BASE, ADC12_B_MEMORY_0);
		break;                                // Clear CPUOFF bit from 0(SR)
	case 14:
		break;                         // Vector 14:  ADC12BMEM1
	case 16:
		break;                         // Vector 16:  ADC12BMEM2
	case 18:
		break;                         // Vector 18:  ADC12BMEM3
	case 20:
		break;                         // Vector 20:  ADC12BMEM4
	case 22:
		break;                         // Vector 22:  ADC12BMEM5
	case 24:
		break;                         // Vector 24:  ADC12BMEM6
	case 26:
		break;                         // Vector 26:  ADC12BMEM7
	case 28:
		break;                         // Vector 28:  ADC12BMEM8
	case 30:
		break;                         // Vector 30:  ADC12BMEM9
	case 32:
		break;                         // Vector 32:  ADC12BMEM10
	case 34:
		break;                         // Vector 34:  ADC12BMEM11
	case 36:
		break;                         // Vector 36:  ADC12BMEM12
	case 38:
		break;                         // Vector 38:  ADC12BMEM13
	case 40:
		break;                         // Vector 40:  ADC12BMEM14
	case 42:
		break;                         // Vector 42:  ADC12BMEM15
	case 44:
		break;                         // Vector 44:  ADC12BMEM16
	case 46:
		break;                         // Vector 46:  ADC12BMEM17
	case 48:
		break;                         // Vector 48:  ADC12BMEM18
	case 50:
		break;                         // Vector 50:  ADC12BMEM19
	case 52:
		break;                         // Vector 52:  ADC12BMEM20
	case 54:
		break;                         // Vector 54:  ADC12BMEM21
	case 56:
		break;                         // Vector 56:  ADC12BMEM22
	case 58:
		break;                         // Vector 58:  ADC12BMEM23
	case 60:
		break;                         // Vector 60:  ADC12BMEM24
	case 62:
		break;                         // Vector 62:  ADC12BMEM25
	case 64:
		break;                         // Vector 64:  ADC12BMEM26
	case 66:
		break;                         // Vector 66:  ADC12BMEM27
	case 68:
		break;                         // Vector 68:  ADC12BMEM28
	case 70:
		break;                         // Vector 70:  ADC12BMEM29
	case 72:
		break;                         // Vector 72:  ADC12BMEM30
	case 74:
		break;                         // Vector 74:  ADC12BMEM31
	case 76:
		break;                         // Vector 76:  ADC12BRDY
	default:
		break;
	}
}

