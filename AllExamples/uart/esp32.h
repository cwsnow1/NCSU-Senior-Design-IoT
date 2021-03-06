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
void ESP32_ssid(char* ssid);
void ESP32_pass(char* pass);
void ESP32_connString(char* connString);
void ESP32_telemetry(char* pass, int value);
void ESP32_addTelemetry(char* addTelemetry);
void ESP32_removeTelemetry(char* removeTelemetry);



#endif /* ESP32_H_ */
