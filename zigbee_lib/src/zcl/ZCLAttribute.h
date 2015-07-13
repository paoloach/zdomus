/*
 * ZCLAttribute.h
 *
 *  Created on: 22/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLATTRIBUTE_H_
#define ZCLATTRIBUTE_H_

#include <exception>
#include <boost/signals2.hpp>
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
	enum Status {
		Undefined,
		NotAvailable,
		NotSupported,
		Available,
		Requesting

	};

	typedef boost::signals2::signal<void()> OnChangeSignal;
	typedef boost::signals2::signal<void ()>  signal_t;
public:
	ZCLAttribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent,int identifier, ZCLTypeDataType zclType, const std::string & name, bool readOnly);
	virtual ~ZCLAttribute();
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
	virtual boost::signals2::connection  onChange(OnChangeSignal::slot_type changeSignal);
protected:
	void sendValueToDevice(uint8_t dataLen, uint8_t * data);
protected:
	const std::shared_ptr<ZigbeeDevice> & zigbeeDevice;
	Cluster * parent;
	int identifier;
	Status status;
	std::string name;
	bool readOnly;
	OnChangeSignal changeSignal;
	ZCLTypeDataType zclType;

};

} /* namespace zigbee */

#endif /* ZCLATTRIBUTE_H_ */
