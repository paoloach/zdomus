/*
 * zigbeeConfig.h
 *
 *  Created on: 29/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZIGBEECONFIG_H_
#define ZIGBEECONFIG_H_

static const unsigned char ANNUNCE_MSG = 0x01;
static const unsigned char REQ_SIMPLE_DESC = 0x02;
static const unsigned char SIMPLE_DESC = 0x03;
static const unsigned char REQ_ACTIVE_ENDPOINTS = 0x04;
static const unsigned char ACTIVE_ENDPOINTS = 0x05;
static const unsigned char REQ_ATTRIBUTE_VALUES = 0x06;
static const unsigned char ATTRIBUTE_VALUES = 0x07;
static const unsigned char REQ_SEND_CMD_VALUES = 0x08;
static const unsigned char REQ_WRITE_ATTRIBUTE_VALUE = 0x09;
static const unsigned char REQ_ALL_NODES = 0x0A;
static const unsigned char REQ_BIND_TABLE = 0x0C;
static const unsigned char BIND_TABLE = 0x0D;
static const unsigned char REQ_ADD_BIND_TABLE_ENTRY = 0x0E;
static const unsigned char REQ_REMOVE_BIND_TABLE_ENTRY = 0x0F;
static const unsigned char REQ_RESET=0x10;
static const unsigned char INFO_MESSAGE=0x20;
static const unsigned char ATTRIBUTE_VALUE_REQ_ERROR = 0x40;
static const unsigned char ACTIVE_EP_REQ_ERROR = 0x41;

static const int Z_EXTADDR_LEN  = 8;


#endif /* ZIGBEECONFIG_H_ */
