/*
 * ZCLenum8bitAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLenum8bitAttribute.h"

#include "../Cluster.h"

namespace zigbee {

    ZCL_enum8bit_Attribute::ZCL_enum8bit_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                                   std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeenum8>(zigbeeDevice, parent, identifier, name, readOnly) {
        zclType = ZCLTypeDataType::ZCLTypeenum8;
    }

    ZCL_enum8bit_Attribute::~ZCL_enum8bit_Attribute() {
    }

    void ZCL_enum8bit_Attribute::sendValue(uint8_t newValue) {
        sendValueToDevice(1, &newValue);
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_enum8bit_Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    boost::any ZCL_enum8bit_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

} /* namespace zigbee */
