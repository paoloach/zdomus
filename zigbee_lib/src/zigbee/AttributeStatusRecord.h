/*
 * AttributeStatusRecord.h
 *
 *  Created on: 23/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTESTATUSRECORD_H_
#define ATTRIBUTESTATUSRECORD_H_

#include "ZigbeeTypes.h"

struct AttributeStatusRecord {
	ZigbeeAttributeId attributeId;
	uint8_t status;
	ZigbeeAttributeDataType attributeDataType;
	int dataLen;
	uint8_t data[256];
};


#endif /* ATTRIBUTESTATUSRECORD_H_ */
