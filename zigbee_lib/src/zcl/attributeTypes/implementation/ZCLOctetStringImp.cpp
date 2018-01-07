//
// Created by developer on 11/17/15.
//
#include <string>
#include <sstream>
#include <boost/spirit/include/karma.hpp>
#include "ZCLOctetStringImp.h"
#include "zcl/exceptions/NoVectorUInt8Exception.h"

namespace zigbee {


    std::string ZCLOctetStringImpl::getStrValue() const {
        using boost::spirit::karma::int_;
        using boost::spirit::karma::generate_delimited;
        using boost::spirit::ascii::space;
        std::string result;
        std::back_insert_iterator<std::string> sink(result);

        generate_delimited(sink, int_ % ',', space, value);
        return result;
    }

    std::any ZCLOctetStringImpl::getValue() const {
        if (status != Available) {
            throw ZCLAttributeNotAvailableException(parent, identifier);
        }
        return std::any(value);
    }

    void ZCLOctetStringImpl::setValue(std::any &anyValue)  {
        if (anyValue.type() == typeid(std::vector<uint8_t>)) {
            value = std::any_cast<std::vector<uint8_t>>(anyValue);
        } else {
            throw NoVectorUInt8Exception(anyValue);
        }
    }

    std::ostream &operator<<(std::ostream &out, const ZCLOctetStringImpl *attribute) {
        std::copy(attribute->value.begin(), attribute->value.end(), std::ostream_iterator<int>(out << " "));
        return out;
    }

    void ZCLOctetStringImpl::setRawValue(uint8_t *rawData) {
        uint8_t len = *rawData;
        value.clear();
        for (int i = 0; i < len; i++) {
            rawData++;
            value.push_back(*rawData);
        }
    }


} /* namespace zigbee */