/*
 * ZigbeeTypes.h
 *
 *  Created on: 23/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZigbeeTYPES_H_
#define ZigbeeTYPES_H_

#include <cstdint>
#include <ostream>
#include <vector>


using ZigbeeEndpoint = uint8_t;
using ZigbeeClusterId = uint16_t;
using ZigbeeNwkAddress = uint16_t;
using ZigbeeAttributeId = uint16_t;
using ZigbeeAttributeDataType = uint8_t;
using ZigbeeAttributeCmdId = uint8_t;
using ZigbeeClusterCmdId = uint16_t;


class ZigbeeAttributeIds : public std::vector<ZigbeeAttributeId> {
public:
    ZigbeeAttributeIds() {}

    ZigbeeAttributeIds(std::vector<ZigbeeAttributeId> &&attributes) :
            std::vector<ZigbeeAttributeId>(attributes) {};

    friend std::ostream &operator<<(std::ostream &out, const ZigbeeAttributeIds &attributeIds);

    friend std::istream &operator>>(std::istream &in, ZigbeeAttributeIds &attributeIds);
};

#endif /* ZigbeeTYPES_H_ */
