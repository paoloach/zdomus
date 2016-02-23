//
// Created by developer on 11/17/15.
//

#ifndef ZIGBEE_LIB_ZCLOCTETSTRING_H
#define ZIGBEE_LIB_ZCLOCTETSTRING_H

#include <string>
#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {
    class ZCLOctetString : public ZCLAttribute {
    public:
        ZCLOctetString(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, Cluster *parent, ZigbeeClusterId identifier,
                       std::experimental::string_view name, bool readOnly);

        virtual ~ZCLOctetString() { }

    public:
        virtual boost::any getValue() const override;

        virtual void sendValue(const std::string &newValue);

        static constexpr ZCLTypeDataType type = ZCLTypeDataType::ZCLTypeStringOctect;

        static std::string name() {
            return "OctectString";
        }

    private:
        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData);

        friend std::ostream &operator<<(std::ostream &out, const ZCLOctetString *);

    private:
        std::vector<uint8_t> value;
    };
}


#endif //ZIGBEE_LIB_ZCLOCTETSTRING_H
