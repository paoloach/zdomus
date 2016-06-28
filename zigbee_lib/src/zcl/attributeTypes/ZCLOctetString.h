//
// Created by developer on 11/17/15.
//

#ifndef ZIGBEE_LIB_ZCLOCTETSTRING_H
#define ZIGBEE_LIB_ZCLOCTETSTRING_H

#include <string>
#include <sstream>
#include <boost/spirit/include/karma.hpp>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {
    class ZCLOctetString : public ZCLAttributeTmpl<ZCLTypeDataType::ZCLTypeStringOctect> {
    public:
        ZCLOctetString(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                       std::experimental::string_view name, bool readOnly);

        virtual ~ZCLOctetString() { }

    public:
        virtual boost::any getValue() const override;
        virtual std::string getStrValue() const {
            using boost::spirit::karma::int_;
            using boost::spirit::karma::generate_delimited;
            using boost::spirit::ascii::space;
            std::string  result;
            std::back_insert_iterator<std::string> sink(result);

            generate_delimited(sink, int_ % ',',  space, value);
            return result;
        }

        virtual void sendValue(const std::string &newValue);

        static std::string name() {
            return "OctectString";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData)override;
        virtual void internalSetValue(uint8_t * rawData) override ;

        friend std::ostream &operator<<(std::ostream &out, const ZCLOctetString *);

    private:
        std::vector<uint8_t> value;
    };
}


#endif //ZIGBEE_LIB_ZCLOCTETSTRING_H
