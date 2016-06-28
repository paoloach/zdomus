/*
 * ZCLuint16Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/endian/conversion.hpp>
#include "ZCLint16Attribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_int16_Attribute::ZCL_int16_Attribute(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                                             ZigbeeClusterId identifier, std::experimental::string_view name,
                                             bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeSInt16>(zigbeeDevice, parent, identifier, name, readOnly){
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) {
                                                        setValue(rawData);
                                                    });
        }
    }

    boost::any ZCL_int16_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCL_int16_Attribute::sendValue(int16_t newValue) {
        sendValueToDevice(2, (uint8_t *) &newValue);
    }

    void ZCL_int16_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        value = boost::endian::little_to_native( *(int16_t *) rawData->data);
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_int16_Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCL_int16_Attribute::internalSetValue(uint8_t *rawData) {
        value = boost::endian::little_to_native( *(int16_t *) rawData);
    }


} /* namespace zigbee */
