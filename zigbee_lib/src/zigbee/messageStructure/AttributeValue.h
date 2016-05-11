/*
 * AttributeValue.h
 *
 *  Created on: 05/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTEVALUE_H_
#define ATTRIBUTEVALUE_H_

#include <ostream>
#include <stdint.h>
#include "../zigbeeConfig.h"
#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"

namespace zigbee {
    struct __attribute__ ((__packed__)) AttributeValue {
        AttributeValue(NwkAddr nwkAddr, EndpointID endpointId, ClusterID clusterId,
                       ZigbeeAttributeId attribute) noexcept:
                generticDataMsg{REQ_ATTRIBUTE_VALUES}, nwkAddr{nwkAddr.getId()}, endpoint{endpointId.getId()},
                cluster{clusterId.getId()}, attribute{attribute} {

        }

        AttributeValue() : nwkAddr(0), endpoint(0), cluster(0), numAttr(0) {
            generticDataMsg.msgCode = REQ_ATTRIBUTE_VALUES;
        }

        GenericMessage generticDataMsg;
        ZigbeeNwkAddress nwkAddr;
        ZigbeeEndpoint endpoint;
        ZigbeeClusterId cluster;
        uint8_t numAttr;
        ZigbeeAttributeId attribute[25];
    };

    std::ostream & operator<<(  std::ostream &out,  const AttributeValue &attribute    ){
        out << "{" << attribute.nwkAddr << ":" << attribute.endpoint << ":" << attribute.cluster << ":" << attribute.attribute;
        out << " numAttr" << attribute.numAttr <<  " [";
        uint8_t  const * iter = reinterpret_cast<uint8_t  const *>(&attribute);
        uint8_t  const * end = reinterpret_cast<uint8_t  const *>(&attribute)+ sizeof(AttributeValue);
        for ( ; iter < end; iter++){
            out << "0x" << std::hex << static_cast<uint32_t >(*iter) << " ";
        }
        out << " ]" << "}";
        return out;
    }

}

#endif /* ATTRIBUTEVALUE_H_ */
