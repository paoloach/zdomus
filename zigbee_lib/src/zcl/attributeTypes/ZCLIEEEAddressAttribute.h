/*
 * ZCLIEEEAddressAttribute.h
 *
 *  Created on: 12/set/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLIEEEADDRESSATTRIBUTE_H_
#define ZCLIEEEADDRESSATTRIBUTE_H_

#include "../ZCLAttribute.h"
#include "../../zigbee/AttributeStatusRecord.h"

namespace zigbee {

class ZCLIEEEAddressAttribute : public ZCLAttribute {
private:
	union Value {
		uint64_t data;
		uint8_t raw[8];
	};
public:
	ZCLIEEEAddressAttribute(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent, ZigbeeClusterId identifier, const std::string & name, bool readOnly);
	virtual ~ZCLIEEEAddressAttribute();
public:
	virtual  boost::any getValue() const override;
	virtual  const uint8_t *   getRawValue() const;
	virtual void sendValue(uint64_t value);
    static constexpr ZCLTypeDataType type=ZCLTypeDataType::ZCLTypeIEEEaddress;
	static std::string name() {
		return "IEEEAddress";
	}
private:
	virtual void internalSetValue(std::shared_ptr<AttributeStatusRecord>  rawData);
private:
	Value value;
};

} /* namespace zigbee */

#endif /* ZCLIEEEADDRESSATTRIBUTE_H_ */
