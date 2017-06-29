//
// Created by developer on 11/17/15.
//

#include "ZCLOctetString.h"
#include "../Cluster.h"

namespace zigbee {

    ZCLOctetString::ZCLOctetString(ZigbeeDevice * zigbeeDevice, Cluster *parent,
                                   ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly) :
            ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeStringOctect>(zigbeeDevice, parent, identifier, name, readOnly){
    }


    boost::any ZCLOctetString::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return boost::any(value);
    }

    void ZCLOctetString::sendValue(const std::string & /*newValue*/) {
        uint8_t data[1 + value.size()];
        data[0] = (uint8_t) value.size();
        int i = 1;
        for (auto &val: value) {
            data[i] = val;
            i++;
        }
        sendValueToDevice((uint8_t) (1 + value.size()), data);
    }

    void ZCLOctetString::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {

        uint8_t len= rawData->data[0];
        value.clear();
        std::copy(rawData->data.begin()+1, rawData->data.begin()+1+len,std::back_inserter(value));
    }

    std::ostream &operator<<(std::ostream &out, const ZCLOctetString *attribute) {
        std::copy(attribute->value.begin(), attribute->value.end(), std::ostream_iterator<int>(out << " "));
        return out;
    }

    void ZCLOctetString::internalSetValue(uint8_t *rawData) {
        uint8_t len = *rawData;
        value.clear();
        for (int i = 0; i < len; i++) {
            rawData++;
            value.push_back(*rawData);
        }
    }


} /* namespace zigbee */