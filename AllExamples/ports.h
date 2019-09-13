/*
 * ports.h
 *
 *  Created on: Apr 20, 2019
 *      Author: Caleb
 */
#include "i2c/sensor_i2c.h"
#include "uart/uart.h"
#include "adc/adc.h"

#ifndef PORTS_H_
#define PORTS_H_

void init_ports(void);
void init_port8(void);

#endif /* PORTS_H_ */
