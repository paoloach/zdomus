//
// Created by paolo on 10/05/16.
//
#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/ReadAttributeResponseErrorMsg.h>
#include "AttributeValueReqError.h"

namespace zigbee {
    void AttributeValueReqError::operator()(unsigned char *data, int) {
        ReadAttributeResponseErrorMsg *response = reinterpret_cast<ReadAttributeResponseErrorMsg *>(data);
        BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  " << *response;
        AttributeKey key(NwkAddr(response->nwkAddr), response->endpoint, response->cluster, response->attribute);
        auto attributeStatusRecord = std::make_shared<AttributeStatusRecord>();
        attributeStatusRecord->attributeId = response->attribute;
        attributeStatusRecord->status = response->status;
        if (attributeValueSignalMap.count(key) > 0) {
            attributeValueSignalMap.execute(key, attributeStatusRecord);
        }
    }
}

