/*
 * AttributeValue.h
 *
 *  Created on: 05/ago/2014
 *      Author: Paolo Achdjian
 */

#ifndef ATTRIBUTEVALUE_H_
#define ATTRIBUTEVALUE_H_

#include <ostream>
#include <array>
#include <stdint.h>
#include <boost/endian/conversion.hpp>
#include "../zigbeeConfig.h"
#include "../ZigbeeTypes.h"
#include "GenericMessage.h"
#include "../NwkAddr.h"
#include "../EndpointID.h"
#include "../ClusterID.h"
#include "../AttributeKey.h"

namespace zigbee {
    struct __attribute__ ((__packed__)) AttributeValue {
        AttributeValue(const AttributeKey &key) noexcept:
                generticDataMsg{REQ_ATTRIBUTE_VALUES}, nwkAddr{key.networkAddress.getId()}, endpoint{key.endpoint.getId()}, cluster{key.clusterId.getId()} {
            numAttr = 1;
            this->attribute[0] = key.attributeId;
        }

        AttributeValue(NwkAddr nwkAddr, EndpointID endpointId, ClusterID clusterId, std::vector<ZigbeeAttributeId> & attributes) noexcept:
                generticDataMsg{REQ_ATTRIBUTE_VALUES}, nwkAddr{nwkAddr.getId()}, endpoint{endpointId.getId()}, cluster{clusterId.getId()} {
            numAttr = attributes.size();
            for (size_t i= 0 ; i < attributes.size() && i < 25; i++) {
                this->attribute[i] = attributes[i];
            }
        }

        AttributeValue() : nwkAddr(0), endpoint(0), cluster(0), numAttr(0) {
            generticDataMsg.msgCode = REQ_ATTRIBUTE_VALUES;
        }

        std::vector<uint8_t> serialize(){
            std::vector<uint8_t> buffer(7+numAttr*2);

            buffer[0] = REQ_ATTRIBUTE_VALUES;
            buffer[1] = nwkAddr&0xFF;
            buffer[2] = (nwkAddr>>8)&0xFF;
            buffer[3] = endpoint;
            buffer[4] = cluster&0xFF;
            buffer[5] = (cluster>>8)&0xFF;
            buffer[6] = numAttr;
            auto iter = buffer.begin()+7;
            for (int i=0; i< numAttr; i++){
                *iter = attribute[i] & 0xFF;
                iter++;
                *iter = (attribute[i]  >> 8)& 0xFF;
                iter++;
            }

            return buffer;
        };

        GenericMessage generticDataMsg;
        ZigbeeNwkAddress nwkAddr;
        ZigbeeEndpoint endpoint;
        ZigbeeClusterId cluster;
        uint8_t numAttr;
        ZigbeeAttributeId attribute[25];
    };

    std::ostream &operator<<(std::ostream &out, const AttributeValue &attribute) {
        out << "{" << attribute.nwkAddr << ":" << attribute.endpoint << ":" << attribute.cluster << ":" << attribute.attribute;
        out << " numAttr" << attribute.numAttr << " [";
        uint8_t const *iter = reinterpret_cast<uint8_t const *>(&attribute);
        uint8_t const *end = reinterpret_cast<uint8_t const *>(&attribute) + sizeof(AttributeValue);
        for (; iter < end; iter++) {
            out << "0x" << std::hex << static_cast<uint32_t >(*iter) << " ";
        }
        out << " ]" << "}";
        return out;
    }

}

#endif /* ATTRIBUTEVALUE_H_ */
