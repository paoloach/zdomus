/*
 * ZCLuint16Attribute.cpp
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#include <boost/endian/conversion.hpp>
#include "ZCLuint24Attribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_uint24_Attribute::ZCL_uint24_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                                               std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeUInt24>(zigbeeDevice, parent, identifier, name, readOnly) {
    }

    boost::any ZCL_uint24_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCL_uint24_Attribute::sendValue(uint32_t newValue) {
        sendValueToDevice(3, (uint8_t *) &newValue);
    }

    void ZCL_uint24_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        Converter converter;
        converter.raw[0] = rawData->data[0];
        converter.raw[1] = rawData->data[1];
        converter.raw[2] = rawData->data[2];
        converter.raw[3] = 0;
        value = boost::endian::little_to_native(converter.value);
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_uint24_Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCL_uint24_Attribute::internalSetValue(uint8_t *rawData) {
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        converter.raw[2] = *(rawData + 2);
        converter.raw[3] = 0;
        value = boost::endian::little_to_native(converter.value);
    }


} /* namespace zigbee */
