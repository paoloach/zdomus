/*
 * ZCLAttribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLATTRIBUTEIMPL_H_
#define ZCLATTRIBUTEIMPL_H_

#include <functional>
#include <exception>
#include <list>
#include <any>
#include <memory>
#include <experimental/string_view>
#include <boost/endian/conversion.hpp>
#include <boost/log/trivial.hpp>
#include <utility>

#include "src/zcl/ZCLDataType.h"
#include "src/zigbee/AttributeStatusRecord.h"
#include "src/zigbee/messageStructure/ReadAttributeResponseMessage.h"
#include "src/zigbee/ResponseCallback.h"
#include "src/zcl/ZCLAttribute.h"

namespace zigbee {

    class Cluster;

    class ZigbeeDevice;


    template<ZCLTypeDataType T>
    class ZclAttributeRawValueImpl : public ZclAttributeRawValue {
    public:
        ZclAttributeRawValueImpl() {
            type = T;
        }

        void operator()(const std::string &) override {}

        void operator()(int64_t) override {}
    };

    class ZCLAttributeImpl : public virtual ZCLAttribute {
    public:


    public:
        ZCLAttributeImpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, int identifier, ZCLTypeDataType zclType,
                         std::string_view name, bool readOnly);

        virtual ~ZCLAttributeImpl() = default;

    public:
        ZCLTypeDataType getZCLType() override {
            return zclType;
        }

        void setValue(AttributeResponse &attributeResponse) override;

        void setValue(uint8_t status, uint8_t dataType, uint8_t *rawData) override;

        void setStatus(uint8_t status) override;

        void requestValue(std::unique_ptr<ResponseCallback<ZCLAttribute *>> &&callback) override;

        bool isAvailable() const override { return status == Available; }

        bool isUnsupported() const override { return status == NotSupported; }

        Status getStatus() override { return status; }

        int getIdentifier() const override { return identifier; }

        std::string_view getName() const override { return name; }

        bool isReadOnly() const override { return readOnly; }

        Cluster *getClusterParent() override { return parent; };

    protected:
        void sendValueToDevice(uint8_t dataLen, uint8_t *data);

    protected:
        ZigbeeDevice *zigbeeDevice;
        Cluster *parent;
        int identifier;
        Status status;
        std::string_view name;
        bool readOnly;
        ZCLTypeDataType zclType;
    };

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeStringChar>::operator()(const std::string &str) {
        rawData.push_back(str.length());
        for (char c: str) {
            rawData.push_back(static_cast<uint8_t >(c));
        }
    }


    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLType8bitBitmap>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLType16bitBitmap>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint) value >> 8) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLType32bitBitmap>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 16) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 24) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeBool>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeenum8>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeSInt8>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeSInt16>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeSInt24>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 16) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeSInt32>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 16) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 24) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt8>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt16>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt24>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 16) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt32>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 16) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 24) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUInt48>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint64_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint64_t) value >> 16) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint64_t) value >> 24) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint64_t) value >> 32) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint64_t) value >> 40) & 0xFF));
    }

    template<>
    inline void ZclAttributeRawValueImpl<ZCLTypeDataType::ZCLTypeUTCTime>::operator()(int64_t value) {
        value = boost::endian::native_to_little(value);
        rawData.push_back(static_cast<uint8_t >(value));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 8) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 16) & 0xFF));
        rawData.push_back(static_cast<uint8_t >(((uint32_t) value >> 24) & 0xFF));
    }


} /* namespace zigbee */

#endif /* ZCLATTRIBUTE_H_ */
