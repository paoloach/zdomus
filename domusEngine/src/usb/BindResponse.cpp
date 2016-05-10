//
// Created by paolo on 22/04/16.
//

#include <boost/endian/conversion.hpp>
#include "BindResponse.h"


using namespace boost::endian;

namespace zigbee {
    BindResponse::BindResponse(uint8_t *&data) {
        srcAddr.setId(little_to_native(*(uint16_t *) data));
        data += 2;
        srcEP.setId(*data++);
        clusterId.setId(little_to_native(*(uint16_t *) data));
        data += 2;
        dstAddr.setId(little_to_native(*(uint16_t *) data));
        data += 2;
        dstEP.setId(*data++);
    }
}

