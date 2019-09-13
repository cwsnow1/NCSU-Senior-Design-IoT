/*
 * sensor_i2c.c
 *
 *  Created on: Apr 8, 2019
 *      Author: caleb
 */

#include "sensor_i2c.h"
#include "sht35.h"
#include "uart/esp32.h"

#ifdef I2C
extern uint8_t RXDATA[];
#else
uint8_t rxdata[2];
#endif

uint8_t count = 0;


void I2C_initPorts(void)
{
    // Configure Pins for I2C
    //Set P7.0 and P7.1 as Primary Module Function Input.
    /*
     * Select Port 7
     * Set Pin 0, 1 to input Primary Module Function, (UCB2SIMO/UCB2SDA, UCB2SOMI/UCB2SCL).
     */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P7,
    GPIO_PIN0 + GPIO_PIN1,
                                               GPIO_PRIMARY_MODULE_FUNCTION);
}

void I2C_initReceive(void)
{
    EUSCI_B_I2C_setMode(EUSCI_B2_BASE, EUSCI_B_I2C_RECEIVE_MODE);
    EUSCI_B_I2C_clearInterrupt(
            EUSCI_B2_BASE,
            EUSCI_B_I2C_RECEIVE_INTERRUPT0 + EUSCI_B_I2C_BYTE_COUNTER_INTERRUPT
                    + EUSCI_B_I2C_NAK_INTERRUPT);

    //Enable master Receive interrupt
    EUSCI_B_I2C_enableInterrupt(
            EUSCI_B2_BASE,
            EUSCI_B_I2C_RECEIVE_INTERRUPT0 + EUSCI_B_I2C_BYTE_COUNTER_INTERRUPT
                    + EUSCI_B_I2C_NAK_INTERRUPT);
    EUSCI_B_I2C_masterReceiveStart(EUSCI_B2_BASE);
    count = 0;
}

void I2C_init(void)
{
    //Initialize Master
    EUSCI_B_I2C_initMasterParam param = { 0 };
    param.selectClockSource = EUSCI_B_I2C_CLOCKSOURCE_SMCLK;
    param.i2cClk = CS_getSMCLK();
    param.dataRate = EUSCI_B_I2C_SET_DATA_RATE_400KBPS;
    param.byteCounterThreshold = 1;
    param.autoSTOPGeneration = EUSCI_B_I2C_NO_AUTO_STOP;
    EUSCI_B_I2C_initMaster(EUSCI_B2_BASE, &param);

    //Specify slave address
    EUSCI_B_I2C_setSlaveAddress(EUSCI_B2_BASE,
    SLAVE_ADDRESS);

    //Set in transmit mode
    EUSCI_B_I2C_setMode(EUSCI_B2_BASE,
    EUSCI_B_I2C_TRANSMIT_MODE);

    //Enable I2C Module to start operations
    EUSCI_B_I2C_enable(EUSCI_B2_BASE);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B0_VECTOR)))
#endif
void USCIB2_ISR(void)
{
    switch (__even_in_range(UCB2IV, USCI_I2C_UCBIT9IFG))
    {
    case USCI_NONE:             // No interrupts break;
        break;
    case USCI_I2C_UCALIFG:      // Arbitration lost
        break;
    case USCI_I2C_UCNACKIFG:    // NAK received (master only)
        //EUSCI_B_I2C_masterReceiveStart(EUSCI_B0_BASE);
        break;
    case USCI_I2C_UCSTTIFG: // START condition detected with own address (slave mode only)
        break;
    case USCI_I2C_UCSTPIFG:     // STOP condition detected (master & slave mode)
        break;
    case USCI_I2C_UCRXIFG3:     // RXIFG3
        break;
    case USCI_I2C_UCTXIFG3:     // TXIFG3
        break;
    case USCI_I2C_UCRXIFG2:     // RXIFG2
        break;
    case USCI_I2C_UCTXIFG2:     // TXIFG2
        break;
    case USCI_I2C_UCRXIFG1:     // RXIFG1
        break;
    case USCI_I2C_UCTXIFG1:     // TXIFG1
        break;
    case USCI_I2C_UCRXIFG0:     // RXIFG0
        // Get RX data
        RXDATA[count] = EUSCI_B_I2C_masterReceiveSingle(EUSCI_B2_BASE);
        if (++count >= RXCOUNT)
        {
            EUSCI_B_I2C_masterReceiveMultiByteStop(EUSCI_B2_BASE);
        }
        break; // Vector 24: RXIFG0 break;
    case USCI_I2C_UCTXIFG0:     // TXIFG0
        break;
    case USCI_I2C_UCBCNTIFG:    // Byte count limit reached (UCBxTBCNT)
        break;
    case USCI_I2C_UCCLTOIFG:    // Clock low timeout - clock held low too long
        break;
    case USCI_I2C_UCBIT9IFG: // Generated on 9th bit of a transmit (for debugging)
        break;
    default:
        break;
    }
}
