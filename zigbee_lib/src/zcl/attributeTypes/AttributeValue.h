//
// Created by paolo on 10/06/16.
//

#ifndef ZIGBEE_LIB_ATTRIBUTEVALUE_H
#define ZIGBEE_LIB_ATTRIBUTEVALUE_H

#include <string>
#include <boost/lexical_cast.hpp>

namespace zigbee {
    template<typename ValueType>
    class AttributeValueTmpl {
    public:
        virtual std::string getStrValue() const {
            return boost::lexical_cast<std::string>(value);
        }
    protected:
        ValueType value;
    };
}

#endif //ZIGBEE_LIB_ATTRIBUTEVALUE_H
