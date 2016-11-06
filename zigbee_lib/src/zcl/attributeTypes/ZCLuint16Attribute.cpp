/*
 * ZCLuint16Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/endian/conversion.hpp>
#include "ZCLuint16Attribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_uint16_Attribute::ZCL_uint16_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                               ZigbeeClusterId identifier, std::experimental::string_view name,
                                               bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt16>(zigbeeDevice, parent, identifier, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) {
                                                        setValue(rawData);
                                                    });
        }
    }

    boost::any ZCL_uint16_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCL_uint16_Attribute::sendValue(uint16_t newValue) {
        sendValueToDevice(2, (uint8_t *) &newValue);
    }

    void ZCL_uint16_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        boost::endian::little_to_native( *(uint16_t *) rawData->data);
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_uint16_Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCL_uint16_Attribute::internalSetValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(uint16_t *) rawData);

    }


} /* namespace zigbee */
