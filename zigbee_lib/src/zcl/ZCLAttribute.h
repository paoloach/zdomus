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

#include "../zigbee/ZigbeeDevice.h"
#include "ZCLDataType.h"

namespace zigbee {

class Cluster;

class ZCLAttributeNotAvailableException : public std::exception {
public:
	ZCLAttributeNotAvailableException(Cluster * parent,int identifier);
	virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
	virtual std::string getMessage() const _GLIBCXX_USE_NOEXCEPT;
private:
	std::string message;

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
	ZCLAttribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent,int identifier, ZCLTypeDataType zclType, const std::string & name, bool readOnly);
    virtual ~ZCLAttribute() = default;
public:
	virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord>  rawData) = 0;
	virtual boost::any getValue() const = 0;

	virtual ZCLTypeDataType getZCLType() {
		return zclType;
	}
	virtual void setValue(std::shared_ptr<AttributeStatusRecord>  rawData);
	virtual void requestValue();
	virtual bool isAvailable() const {return status == Available;}
	virtual bool isUnsupported() const {return status == NotSupported;}
	virtual Status getStatus() {return status;}
	virtual int getIdentifier() const {return identifier;}
	virtual std::string getName() const {return name;}
	virtual bool isReadOnly() const {return readOnly;}
	virtual ListenerOnChange onChange(std::function<void()> changeSignal){
		if (callbacks.empty()){
			callbacks.push_front(changeSignal);
			return callbacks.begin();
		} else {
			return callbacks.insert(callbacks.begin(), changeSignal);
		}
    };

    virtual void removeOnChangeListener(ListenerOnChange && listener){
        callbacks.erase(listener);
    }
protected:
	void sendValueToDevice(uint8_t dataLen, uint8_t * data);
protected:
	const std::shared_ptr<ZigbeeDevice> & zigbeeDevice;
	Cluster * parent;
	int identifier;
	Status status;
	std::string name;
	bool readOnly;
    OnChangeCallbacks    callbacks;
	ZCLTypeDataType zclType;

};

} /* namespace zigbee */

#endif /* ZCLATTRIBUTE_H_ */
