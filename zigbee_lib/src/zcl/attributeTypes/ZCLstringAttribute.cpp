/*
 * ZCLstringAttribute.cpp
 *
 *  Created on: 25/lug/2014
 *      Author: Paolo Achdjian
 */

#include "ZCLstringAttribute.h"
#include "../Cluster.h"

namespace zigbee {

    ZCL_string_Attribute::ZCL_string_Attribute(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                               ZigbeeClusterId identifier, std::experimental::string_view name,
                                               bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeStringChar>(zigbeeDevice, parent, identifier, name, readOnly) {
    }

    std::any ZCL_string_Attribute::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCL_string_Attribute::sendValue(const std::string & /*newValue*/) {
        uint8_t data[1 + value.length()];
        data[0] = (uint8_t) value.length();
        memcpy(data + 1, value.c_str(), value.length());
        sendValueToDevice((uint8_t) (1 + value.length()), data);
    }

    void ZCL_string_Attribute::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        uint8_t len = rawData->data[0];
        value = std::string();
        value.resize(len);
        std::copy(rawData->data.begin()+1, rawData->data.begin()+1+len, value.begin());
    }

    std::ostream &operator<<(std::ostream &out, const ZCL_string_Attribute *attribute) {
        out << attribute->value;
        return out;
    }

    void ZCL_string_Attribute::internalSetValue(uint8_t *rawData) {
        uint8_t len = *rawData;
        value = std::string();
        value.resize(len);
        for (int i = 0; i < len; i++) {
            value[i] = rawData[i + 1];
        }
        status = Available;
    }


} /* namespace zigbee */
