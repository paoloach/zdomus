//
// Created by paolo on 03/01/18.
//

#ifndef ZIGBEE_LIB_ZCLATTRIBUTE_H
#define ZIGBEE_LIB_ZCLATTRIBUTE_H

#include <functional>
#include <exception>
#include <list>
#include <any>
#include <memory>
#include "zigbee/ResponseCallback.h"
#include "ZCLDataType.h"
#include "zcl/exceptions/ZCLAttributeNotAvailableException.h"

class AttributeStatusRecord;

namespace zigbee {
    class ZclAttributeRawValue;
    class Cluster;
    class AttributeResponse;
    class ZCLAttribute;

    class ZclAttributeRawValue {
    public:
        ZclAttributeRawValue() {
            type = ZCLTypeDataType::ZCLTypeInvalid;
        }

        ZCLTypeDataType type;
        std::vector<uint8_t> rawData;

        virtual void operator()(const std::string &str) = 0;

        virtual void operator()(int64_t) =0;

        virtual void operator()(const std::vector<uint8_t> &rawData) {
            this->rawData = rawData;
        }
    };

    class ZCLAttribute {
    public:
        using OnChangeCallbacks = std::list<std::function<void()>>;
        using ListenerOnChange = OnChangeCallbacks::iterator;

        enum Status {
            Undefined,
            NotAvailable,
            NotSupported,
            Available,
            Requesting

        };

    public:
        virtual ZclAttributeRawValue &getAttributeRawValue() = 0;

        virtual std::any getValue() const = 0;

        virtual void setValue(std::any & value) = 0;

        virtual void setRawValue(uint8_t * data)=0;

        virtual std::string getStrValue() const = 0;

        virtual ZCLTypeDataType getZCLType() = 0;

        virtual void setValue(AttributeResponse &attributeResponse)=0;

        virtual void setValue(uint8_t status, uint8_t dataType, uint8_t *rawData)=0;

        virtual void setStatus(uint8_t status)=0;

        virtual void requestValue( std::unique_ptr<ResponseCallback<ZCLAttribute *>> &&callback)=0;

        virtual bool isAvailable() const =0;

        virtual bool isUnsupported() const =0;

        virtual Status getStatus()=0;

        virtual int getIdentifier() const=0;

        virtual std::string_view getName() const =0;

        virtual bool isReadOnly() const =0;

        virtual Cluster *getClusterParent()=0;
    };
}
#endif //ZIGBEE_LIB_ZCLATTRIBUTE_H
