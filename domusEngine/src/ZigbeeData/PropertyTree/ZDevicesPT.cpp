/*
 * ZDevicesPT.cpp
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */

#include <boost/lexical_cast.hpp>
#include "ZDevicesPT.h"

namespace zigbee {
namespace http {

ZDevicesPT::ZDevicesPT(std::shared_ptr<ZDevices>  zDevices) noexcept {
	for (const ZDevice & device : zDevices->getDevices()) {
		add(boost::lexical_cast<std::string>(device.getNwkAddr()),device.getExtAddr());
	}
}

ZDevicesPT::~ZDevicesPT() noexcept {
}

} /* namespace http */
} /* namespace zigbee */
