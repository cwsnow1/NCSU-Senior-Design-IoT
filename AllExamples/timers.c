/*
 * timers.c
 *
 *  Created on: Apr 11, 2019
 *      Author: Caleb
 */
#include "timers.h"


void timer_a_init(uint16_t timer_a_base)
{

    //Start timer in continuous mode sourced by SMCLK
    Timer_A_initContinuousModeParam initContParam = { 0 };
    initContParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_64;
    initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam.timerClear = TIMER_A_DO_CLEAR;
    initContParam.startTimer = false;
    Timer_A_initContinuousMode(timer_a_base, &initContParam);

    //Initiaze compare mode
    Timer_A_clearCaptureCompareInterrupt(timer_a_base,
    TIMER_A_CAPTURECOMPARE_REGISTER_0);

    Timer_A_initCompareModeParam initCompParam = { 0 };
    initCompParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompParam.compareInterruptEnable =
            TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompParam.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    initCompParam.compareValue = COMPARE_VALUE;
    Timer_A_initCompareMode(timer_a_base, &initCompParam);

    Timer_A_startCounter( timer_a_base,
    TIMER_A_CONTINUOUS_MODE);
}




//******************************************************************************
//
//This is the TIMER1_A0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#endif
void TIMER1_A0_ISR (void)
{
	static int i = 0;
    uint16_t compVal = Timer_A_getCaptureCompareCount(TIMER_A1_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0)
            + COMPARE_VALUE;

    // wake up for capture and send
    if((++i % 20) == 0)
    	__bic_SR_register_on_exit(LPM1_bits);

    //Add Offset to CCR0
    Timer_A_setCompareValue(TIMER_A1_BASE,
        TIMER_A_CAPTURECOMPARE_REGISTER_0,
        compVal
        );
}
