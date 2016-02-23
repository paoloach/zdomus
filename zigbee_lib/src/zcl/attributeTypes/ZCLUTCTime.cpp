//
// Created by developer on 11/17/15.
//

#include "ZCLUTCTime.h"
#include "../Cluster.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace zigbee {

    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;
    using boost::gregorian::date;
    using boost::gregorian::Jan;
    using boost::posix_time::seconds;

    ZCLUTCTime::ZCLUTCTime(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent,
                           ZigbeeClusterId identifier, std::experimental::string_view name, bool readOnly) :
            ZCLAttribute(zigbeeDevice, parent, identifier, ZCLTypeDataType::ZCLTypeUTCTime, name, readOnly) {
        if (zigbeeDevice) {
            zigbeeDevice->registerForAttributeValue(parent->getNetworkAddress(), parent->getEndpoint(), parent->getId(),
                                                    identifier,
                                                    [this](std::shared_ptr<AttributeStatusRecord> rawData) {
                                                        setValue(rawData);
                                                    });
        }

    }

    boost::any ZCLUTCTime::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        seconds from2000(value);
        ptime start(boost::gregorian::date(2000, Jan, 1), time_duration(0, 0, 0));
        return boost::any(start + from2000);
    }

    void ZCLUTCTime::sendValue(uint32_t newValue) {
        sendValueToDevice(4, (uint8_t *) &newValue);
    }

    void ZCLUTCTime::internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) {
        Converter converter;
        converter.raw[0] = *rawData->data;
        converter.raw[1] = *(rawData->data + 1);
        converter.raw[2] = *(rawData->data + 2);
        converter.raw[3] = *(rawData->data + 3);
        value = converter.value;
    }

    std::ostream &operator<<(std::ostream &out, const ZCLUTCTime *attribute) {
        out << attribute->value;
        return out;
    }
}