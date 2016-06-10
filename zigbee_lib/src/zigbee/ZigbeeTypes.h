/*
 * ZigbeeTypes.h
 *
 *  Created on: 23/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZigbeeTYPES_H_
#define ZigbeeTYPES_H_

#include <stdint.h>
#include <ostream>
#include <vector>


typedef uint8_t ZigbeeEndpoint;
typedef uint16_t ZigbeeClusterId;
typedef uint16_t ZigbeeNwkAddress;
typedef uint16_t ZigbeeAttributeId;
typedef uint8_t ZigbeeAttributeDataType;
typedef uint8_t ZigbeeAttributeCmdId;
typedef uint16_t ZigbeeClusterCmdId;


class ZigbeeAttributeIds : public std::vector<ZigbeeAttributeId> {
public:
    ZigbeeAttributeIds(){}
    ZigbeeAttributeIds(std::vector<ZigbeeAttributeId> &&attributes) :
            std::vector<ZigbeeAttributeId>(attributes) { };

    friend std::ostream &operator<<(std::ostream &out, const ZigbeeAttributeIds &attributeIds);
};

#endif /* ZigbeeTYPES_H_ */
