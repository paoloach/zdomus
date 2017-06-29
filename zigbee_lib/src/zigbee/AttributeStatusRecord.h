/*
 * AttributeStatusRecord.h
 *
 *  Created on: 23/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTESTATUSRECORD_H_
#define ATTRIBUTESTATUSRECORD_H_

#include <array>
#include "ZigbeeTypes.h"

struct AttributeStatusRecord {
	ZigbeeAttributeId attributeId;
	uint8_t status;
	ZigbeeAttributeDataType attributeDataType;
    std::array<uint64_t , 256> data;
};


#endif /* ATTRIBUTESTATUSRECORD_H_ */
