/*
 * esp32.h
 *
 *  Created on: Apr 20, 2019
 *      Author: Caleb
 */
#include "uart.h"

#ifndef ESP32_H_
#define ESP32_H_

void init_ESP32(void);
void ESP32_transmit_4byte_Array(uint8_t data[4]);
void ESP32_sendData(void);

// Commands
// all commands end with carriage return (\r)
// AT+ssid="ssid"
// AT+pass="password"
// AT+connString="connection_string"
// AT+telemetry="telemetry","value"
// AT+addTelemetry="telemetry"
// AT+removeTelemetry="telemetry"
// AT+clearTelemetry
void ESP32_ssid(uint8_t* ssid);
void ESP32_pass(uint8_t* pass);
void ESP32_connString(uint8_t* connString);
void ESP32_telemetry(uint8_t* telemetry, uint8_t* value);



#endif /* ESP32_H_ */
