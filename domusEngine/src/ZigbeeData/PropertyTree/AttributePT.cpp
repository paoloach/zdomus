/*
 * AttributePT.cpp
 *
 *  Created on: 26/mag/2015
 *      Author: Paolo Achdjian
 */

#include <zcl/ZCLAttribute.h>
#include "AttributePT.h"

namespace zigbee {


AttributePT::AttributePT(const std::shared_ptr<ZCLAttribute>& attribute) {
	add("id", attribute->getIdentifier());
	add("name", attribute->getName());
	add("readOnly", attribute->isReadOnly());
	add("type", attribute->getZCLType());
	add("isAvailable", attribute->isAvailable());
	add("isSupported", !attribute->isUnsupported());
	add("status", attribute->getStatus());
	if (attribute->isAvailable()){
		add("value", boost::any_cast<std::string>(attribute->getValue()));
	}

}


} /* namespace zigbee */
