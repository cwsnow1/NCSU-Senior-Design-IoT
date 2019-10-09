/*
 * sht35.h
 *
 *  Created on: Apr 8, 2019
 *      Author: caleb
 */

#include "driverlib.h"
#include <inttypes.h>

#ifndef SHT35_H_
#define SHT35_H_

#define SHT35

#ifdef SHT35
#define I2C
#define SLAVE_ADDRESS 0x45
#define RXCOUNT (5)
#define RXDATA sht35data
#else
#define SLAVE_ADDRESS (0)
#define RXCOUNT (0)
#define RXDATA rxdata
#endif

// SHT35 Commands
#define HALF_MPS        0x20
#define ONE_MPS         0x21
#define TWO_MPS         0x22
#define FOUR_MPS        0x23
#define TEN_MPS         0x27
//
#define HALF_LOW_RP     0x2F
#define HALF_MED_RP     0x24
#define HALF_HIGH_RP    0x32
//
#define ONE_LOW_RP      0x2D
#define ONE_MED_RP      0x26
#define ONE_HIGH_RP     0x30
//
#define TWO_LOW_RP      0x2B
#define TWO_MED_RP      0x20
#define TWO_HIGH_RP     0x36
//
#define FOUR_LOW_RP     0x29
#define FOUR_MED_RP     0x22
#define FOUR_HIGH_RP    0x34
//
#define TEN_LOW_RP      0x2A
#define TEN_MED_RP      0x21
#define TEN_HIGH_RP     0x37
//

void SHT35_sendCommand(uint8_t MSB, uint8_t LSB);
float SHT35_getTemp(uint8_t data[]);
float SHT35_getHumidity(uint8_t data[]);

#endif /* SHT35_H_ */
