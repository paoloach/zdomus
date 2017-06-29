//
// Created by paolo on 10/05/16.
//
#include <boost/log/trivial.hpp>
#include <zigbee/messageStructure/ReadAttributeResponseErrorMsg.h>
#include <zigbee/AttributeKey.h>
#include "AttributeValueReqError.h"

namespace zigbee {
    void AttributeValueReqError::operator()(unsigned char *data, int) {
        ReadAttributeResponseErrorMsg *response = reinterpret_cast<ReadAttributeResponseErrorMsg *>(data);
        BOOST_LOG_TRIVIAL(error) << "Error on requesting attribute value from  " << *response;
        AttributeKey key(NwkAddr(response->nwkAddr), EndpointID(response->endpoint), ClusterID(response->cluster), response->attribute);
        zigbeeDevice->setAttribute(key, nullptr);
    }
}

