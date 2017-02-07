/*
 * ZCLAttribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLATTRIBUTE_H_
#define ZCLATTRIBUTE_H_

#include <functional>
#include <exception>
#include <list>
#include <boost/any.hpp>
#include <memory>
#include <experimental/string_view>
#include <boost/endian/conversion.hpp>
#include <boost/log/trivial.hpp>
#include <utility>

#include "../zigbee/ZigbeeDevice.h"
#include "ZCLDataType.h"
#include "Callbacks.h"

namespace zigbee {

    class Cluster;

    class ZCLAttributeNotAvailableException : public std::exception {
    public:
        ZCLAttributeNotAvailableException(Cluster *parent, int identifier);

        const char *what() const _GLIBCXX_USE_NOEXCEPT override;

        virtual std::string getMessage() const _GLIBCXX_USE_NOEXCEPT;

    private:
        std::string message;

    };

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

    template<ZCLTypeDataType T>
    class ZclAttributeRawValueImpl : public ZclAttributeRawValue {
    public:
        ZclAttributeRawValueImpl() {
            type = T;
        }

        void operator()(const std::string &) override {}

        void operator()(int64_t) override {}
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
        ZCLAttribute(ZigbeeDevice *zigbeeDevice, Cluster *parent, int identifier, ZCLTypeDataType zclType,
                     std::experimental::string_view name, bool readOnly);

        virtual ~ZCLAttribute() = default;

    public:
        virtual ZclAttributeRawValue &getAttributeRawValue() = 0;

        virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord> rawData) = 0;

        virtual void internalSetValue(uint8_t *rawData) = 0;

        virtual boost::any getValue() const = 0;

        virtual std::string getStrValue() const = 0;

        virtual ZCLTypeDataType getZCLType() {
            return zclType;
        }

        virtual void setValue(std::shared_ptr<AttributeStatusRecord> rawData);

        virtual void setValue(AttributeResponse &attributeResponse);

        virtual void setValue(uint8_t status, uint8_t dataType, uint8_t *rawData);

        virtual void requestValue();

        virtual bool isAvailable() const { return status == Available; }

        virtual bool isUnsupported() const { return status == NotSupported; }

        virtual Status getStatus() { return status; }

        virtual int getIdentifier() const { return identifier; }

        virtual std::experimental::string_view getName() const { return name; }

        virtual bool isReadOnly() const { return readOnly; }

        virtual Cluster *getClusterParent() { return parent; };

        virtual ListenerOnChange onChange(std::function<void()> && changeSignal) {
            return callbacks.add(changeSignal);
        };

        virtual void removeOnChangeListener(ListenerOnChange &listener) {

            callbacks.remove(listener);
            BOOST_LOG_TRIVIAL(info) << "remain " << callbacks.size() << " elements";
        }

    protected:
        void sendValueToDevice(uint8_t dataLen, uint8_t *data);

    protected:
        ZigbeeDevice *zigbeeDevice;
        Cluster *parent;
        int identifier;
        Status status;
        std::experimental::string_view name;
        bool readOnly;
        Callbacks callbacks;
        ZCLTypeDataType zclType;
    };

    template<ZCLTypeDataType T>
    class ZCLAttributeTmpl : public ZCLAttribute {
    public:
        ZCLAttributeTmpl(ZigbeeDevice *zigbeeDevice, Cluster *parent, int identifier,
                         std::experimental::string_view name, bool readOnly) : ZCLAttribute(zigbeeDevice, parent,
                                                                                            identifier, T, name,
                                                                                            readOnly) {}

        ZclAttributeRawValue &getAttributeRawValue() override { return zclAttributeRawValueImpl; }

        static constexpr ZCLTypeDataType type = T;
    protected:
        ZclAttributeRawValueImpl<T> zclAttributeRawValueImpl;
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
