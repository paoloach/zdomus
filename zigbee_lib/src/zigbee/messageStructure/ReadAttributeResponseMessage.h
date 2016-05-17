/*
 * ReadAttributeResponseMessage.h
 *
 *  Created on: 24/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef READATTRIBUTERESPONSEMESSAGE_H_
#define READATTRIBUTERESPONSEMESSAGE_H_

#include "GenericMessage.h"

namespace zigbee {

    struct __attribute__ ((__packed__)) AttributeResponse {
        uint16_t attrID;
        uint8_t status;
        uint8_t dataType;
    };

    struct __attribute__ ((__packed__)) ReadAttributeResponseMessage {
        static const int MAX_DATA_SIZE = 40;
        GenericMessage generticDataMsg;
        uint8_t type;
        uint16_t clusterId;
        uint16_t networkAddr;
        uint8_t endpoint;
        uint16_t panId;
        uint8_t numAttributes;
    };

}

#endif /* READATTRIBUTERESPONSEMESSAGE_H_ */
