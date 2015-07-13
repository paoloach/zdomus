/*
 * AttributeData.h
 *
 *  Created on: 01/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_ATTRIBUTEDATA_H_
#define SRC_ZIGBEEDATA_ATTRIBUTEDATA_H_

#include <vector>

#include "zigbee/messageStructure/ReadAttributeResponseMessage.h"

namespace zigbee {

class AttributeData {
public:
	AttributeData();
	AttributeData(const ReadAttributeResponseMessage & attribute);
	AttributeData & operator=(const ReadAttributeResponseMessage & attribute);
	virtual ~AttributeData();
public:
	bool operator==(const AttributeData & attribute);

	uint8_t getAttrId() const {
		return attrID;
	}

	uint16_t getClusterId() const {
		return clusterId;
	}

	const std::vector<uint8_t> getData() const {
		return data;
	}

	uint8_t getEndpoint() const {
		return endpoint;
	}

	uint16_t getNetworkAddr() const {
		return networkAddr;
	}

	uint16_t getPanId() const {
		return panId;
	}

	uint8_t getStatus() const {
		return status;
	}

	uint8_t getType() const {
		return type;
	}

private:
	uint8_t type;
	uint16_t clusterId;
	uint16_t networkAddr;
	uint8_t endpoint;
	uint16_t panId;
	uint8_t attrID;
	uint8_t status;
	std::vector<uint8_t> data;
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_ATTRIBUTEDATA_H_ */
