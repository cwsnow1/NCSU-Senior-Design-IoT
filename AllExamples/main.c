/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//
#include "driverlib.h"
#include "i2c/sensor_i2c.h"
#include "i2c/sht35.h"
#include "timers.h"
#include "ports.h"
#include "uart/uart.h"
#include "uart/esp32.h"
#include "adc/adc.h"

//
//Set the address for slave module. This is a 7-bit address sent in the
//following format:
//[A6:A5:A4:A3:A2:A1:A0:RS]
//
//A zero in the "RS" position of the first byte means that the master
//transmits (sends) data to the selected slave, and a one in this position
//means that the master receives data from the slave.
//
//*****************************************************************************

extern bool client_connected;
extern uint8_t RXDATA[];

void main(void)
{
    WDT_A_hold(WDT_A_BASE);

    //Set DCO frequency to 8MHz
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);
    //Set ACLK = VLO with frequency divider of 1
    CS_initClockSignal(CS_ACLK, CS_VLOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    //Set SMCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    //Set MCLK = DCO with frequency divider of 1
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    init_ports();

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();
#ifdef ADC
    init_ADC12B();
#endif
#ifdef ADC_A4
    init_ADC12B_memoryBuffer(ADC12_B_MEMORY_0, ADC12_B_INPUT_A4, ADC12_B_IFG0,
    ADC12_B_IE0);
#endif

    UART_init(EUSCI_A0_BASE);
    UART_init(EUSCI_A3_BASE);

    ESP32_ssid("ClickForFreeViruses-2.4G");
    ESP32_pass("u0y8-lokv-bu9x");

    timer_a_init(TIMER_A0_BASE);
    __enable_interrupt();
    // Enable ESp32
    // init_ESP32();

#ifdef I2C
    I2C_init();
#endif
#ifdef SHT35
    SHT35_sendCommand(FOUR_MPS, FOUR_HIGH_RP);
#endif
    while (1)
    {

        //Delay between each transaction
        __bis_SR_register(LPM1_bits + GIE);
#ifdef I2C
        I2C_initReceive();
#endif
#ifdef ADC_A4
        ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_MEMORY_0, ADC12_B_SINGLECHANNEL);
#endif

            ESP32_sendData();


    }
}

