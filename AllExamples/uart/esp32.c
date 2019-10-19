/*
 * esp32.c
 *
 *  Created on: Apr 20, 2019
 *      Author: Caleb
 */
#include "esp32.h"
#include "i2c/sht35.h"
#include "adc/adc.h"
#include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>

extern uint8_t UART_buffer[];
extern uint8_t RXDATA[];
extern uint16_t ADC_A4_value;

void init_ESP32(void)
{
    P8OUT |= 0x2;
    int i, j;
    bool wifi_ip = false;
    bool ok = false;
    while (!wifi_ip)
    {
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (UART_buffer[i] == 'T')
            {
                j = (i + 1) & (BUFFER_SIZE - 1);
                if (UART_buffer[j] == ' ')
                {
                    j = (j + 1) & (BUFFER_SIZE - 1);
                    if (UART_buffer[j] == 'I')
                    {
                        j = (j + 1) & (BUFFER_SIZE - 1);
                        if (UART_buffer[j] == 'P')
                        {
                            wifi_ip = true;
                        }
                    }
                }
            }

        }
    }
    EUSCI_A_UART_transmitString(EUSCI_A3_BASE, "AT+CIPMUX=1\r\n");
    while (!ok)
    {
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (UART_buffer[i] == 'O')
            {
                j = (i + 1) & (BUFFER_SIZE - 1);
                if (UART_buffer[j] == 'K')
                    ok = true;
            }
        }
    }
    ok = false;
    EUSCI_A_UART_transmitString(EUSCI_A3_BASE, "AT+CIPSERVER=1,32001\r\n");
    while (!ok)
    {
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (UART_buffer[i] == 'O')
            {
                j = (i + 1) & (BUFFER_SIZE - 1);
                if (UART_buffer[j] == 'K')
                    ok = true;
            }
        }
    }
    P1OUT &= ~0x1;
}

// LENGTH MUST BE LESS THAN 10
void ESP32_transmitArray(uint8_t data[], uint8_t length)
{
    int i;
    bool ready = false;
    char ascii_length = length + 0x30;
    EUSCI_A_UART_transmitString(EUSCI_A3_BASE, "AT+CIPSEND=0,");
    EUSCI_A_UART_transmitData(EUSCI_A3_BASE, ascii_length);
    EUSCI_A_UART_transmitString(EUSCI_A3_BASE, "\r\n");

    while (!ready)
    {
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (UART_buffer[i] == '>')
                ready = true;
        }
    }
    EUSCI_A_UART_transmitArray(EUSCI_A3_BASE, data, 4);
    EUSCI_A_UART_transmitString(EUSCI_A3_BASE, "\r\n");
}

void ESP32_sendData(void)
{
#ifdef SHT35
	EUSCI_A_UART_transmitData(EUSCI_A3_BASE, '0');
	EUSCI_A_UART_transmitData(EUSCI_A3_BASE, RXDATA[0]);
	EUSCI_A_UART_transmitData(EUSCI_A3_BASE, RXDATA[1]);
#endif
#ifdef ADC_A4
    uint8_t data[2] =
    {   ADC_A4_value >> 8, ADC_A4_value};
    ESP32_transmitArray(data, 2);
#endif
}
void ESP32_ssid(char* ssid);
{
    int n;
    n=sizeof(ssid);
    char* ssid2;
    ssid2[0]='A';
    ssid2[1]='T';
    ssid2[n+2]='\';
    ssid2[n+3]='r';
    for(i=0,i<=n,i++)
    {
        ssid2[i+2]=ssid[i];
    }
    EUSCI_A_UART_transmitData(EUSCI_A3_BASE, ssid2);



}
// all commands end with carriage return (\r)
// AT+ssid="ssid"
