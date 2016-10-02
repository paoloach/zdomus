/*
 * zigbeeConfig.h
 *
 *  Created on: 29/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZIGBEECONFIG_H_
#define ZIGBEECONFIG_H_

#include <cstdint>

static const uint8_t ANNUNCE_MSG = 0x01;
static const uint8_t REQ_SIMPLE_DESC = 0x02;
static const uint8_t SIMPLE_DESC = 0x03;
static const uint8_t REQ_ACTIVE_ENDPOINTS = 0x04;
static const uint8_t ACTIVE_ENDPOINTS = 0x05;
static const uint8_t REQ_ATTRIBUTE_VALUES = 0x06;
static const uint8_t ATTRIBUTE_VALUES = 0x07;
static const uint8_t REQ_SEND_CMD_VALUES = 0x08;
static const uint8_t REQ_WRITE_ATTRIBUTE_VALUE = 0x09;
static const uint8_t REQ_ALL_NODES = 0x0A;
static const uint8_t REQ_BIND_TABLE = 0x0C;
static const uint8_t BIND_TABLE = 0x0D;
static const uint8_t REQ_ADD_BIND_TABLE_ENTRY = 0x0E;
static const uint8_t REQ_REMOVE_BIND_TABLE_ENTRY = 0x0F;
static const uint8_t REQ_RESET=0x10;
static const uint8_t REQ_DEVICE_INFO=0x11;
static const uint8_t DEVICE_INFO=0x12;
static const uint8_t REQ_IEEE_ADDRESS=0x13;
static const uint8_t IEEE_ADDRESS_RESPONSE = 0x14;

static const uint8_t INFO_MESSAGE=0x20;
static const uint8_t ATTRIBUTE_VALUE_REQ_ERROR = 0x40;
static const uint8_t ACTIVE_EP_REQ_ERROR = 0x41;
static const uint8_t IEEE_ADDRESS_RESPONSE_ERROR = 0x42;

static const int Z_EXTADDR_LEN  = 8;


#endif /* ZIGBEECONFIG_H_ */
