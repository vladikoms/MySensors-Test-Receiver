/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik EKblad
 *
 * DESCRIPTION
 * Example sketch showing how to measue light level using a LM393 photo-resistor
 * http://www.mysensors.org/build/light
 */

// Enable debug prints to serial monitor
//#define MY_DEBUG

// Enable and select radio type attached

// See settings in Myconfig.h file

//#define MY_RADIO_NRF24
//#define MY_RADIO_NRF5_ESB
//#define MY_RADIO_RFM69
#define MY_RADIO_RFM95

/**
 * @def MY_RFM95_FREQUENCY
 * @brief The frequency to use.
 *
 * - RFM95_169MHZ
 * - RFM95_315MHZ
 * - RFM95_434MHZ
 * - RFM95_868MHZ
 * - RFM95_915MHZ
 * - Custom frequency in Hz
 *
 * This must match the hardware version of the RFM95 radio.
 * Additional information: https://en.wikipedia.org/wiki/Short_Range_Devices
 */

#define MY_RFM95_FREQUENCY   RFM95_434MHZ

/**
 * @def MY_RFM95_MODEM_CONFIGRUATION
 * @brief RFM95 modem configuration.
 *
 * BW = Bandwidth in kHz
 * CR = Error correction code
 * SF = Spreading factor, chips / symbol
 *
 * | CONFIG                 | BW    | CR  | SF   | Comment
 * |------------------------|-------|-----|------|-----------------------------
 * | RFM95_BW125CR45SF128   | 125   | 4/5 | 128  | Default, medium range
 * | RFM95_BW500CR45SF128   | 500   | 4/5 | 128  | Fast, short range
 * | RFM95_BW31_25CR48SF512 | 31.25 | 4/8 | 512  | Slow, long range
 * | RFM95_BW125CR48SF4096  | 125   | 4/8 | 4096 | Slow, long range
 *
 */

#define MY_RFM95_MODEM_CONFIGRUATION RFM95_BW125CR45SF128

#define MY_RFM95_TX_POWER_DBM (20u)  // Tx Power = 20dBm (100mW) . Realy measured for RA-02: 63mW

#define MY_RFM95_ATC_MODE_DISABLED // Отключение режима ATC

#include <MySensors.h>

uint32_t SLEEP_TIME = 5000; // Sleep time between reads (in milliseconds)

void loop()
{
 Serial.println ("Sending request to gateway...");
 sendHeartbeat();
 int16_t RecSNR = RFM95_getReceivingSNR();
 Serial.print ("Last received packet SNR = ");
 Serial.println (RecSNR);
 int16_t ReceivingRSSI = RFM95_getReceivingRSSI ();
 Serial.print ("Last received packet RSSI = ");
 Serial.println (ReceivingRSSI);
 uint8_t TXPWR = RFM95_getTxPowerLevel();
 Serial.print ("TX Power (dBm) = ");
 Serial.println (TXPWR);
 sleep(SLEEP_TIME);
}



