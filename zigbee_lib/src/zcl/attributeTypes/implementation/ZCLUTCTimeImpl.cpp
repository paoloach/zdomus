//
// Created by developer on 11/17/15.
//

#include "ZCLUTCTimeImpl.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "zcl/exceptions/NoUintException.h"

namespace zigbee {

    union Converter {
        uint32_t value;
        uint8_t raw[4];
    };

    using boost::posix_time::ptime;
    using boost::posix_time::time_duration;
    using boost::gregorian::date;
    using boost::gregorian::Jan;
    using boost::posix_time::seconds;

    std::any ZCLUTCTimeImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        seconds from2000(value);
        ptime start(boost::gregorian::date(2000, Jan, 1), time_duration(0, 0, 0));
        return std::any(start + from2000);
    }


    void ZCLUTCTimeImpl::setValue(std::any &anyValue)  {
        if (anyValue.type() == typeid(uint32_t)) {
            value = std::any_cast<uint32_t>(anyValue);
        } else {
            throw NoUintException(anyValue);
        }
    }



    void ZCLUTCTimeImpl::setRawValue(uint8_t *rawData) {
        Converter converter;
        converter.raw[0] = *rawData;
        converter.raw[1] = *(rawData + 1);
        converter.raw[2] = *(rawData + 2);
        converter.raw[3] = *(rawData + 3);
        value = converter.value;
        status = Available;
    }

    std::ostream &operator<<(std::ostream &out, const ZCLUTCTimeImpl *attribute) {
        out << attribute->value;
        return out;
    }
}