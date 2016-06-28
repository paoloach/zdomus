/*
 * ZCLuint8Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include "ZCLuint8Attribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_uint8_Attribute::ZCL_uint8_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                             std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt8>(zigbeeDevice, parent, identifier, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) { setValue(rawData); });
        }
    }


    boost::any ZCL_uint8_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCL_uint8_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = *rawData->data;
    }

    void ZCL_uint8_Attribute::sendValue(uint8_t newValue) {
        sendValueToDevice(1, &newValue);
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_uint8_Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCL_uint8_Attribute::internalSetValue(uint8_t *rawData) {
        value = *rawData;
    }


} /* namespace zigbee */
