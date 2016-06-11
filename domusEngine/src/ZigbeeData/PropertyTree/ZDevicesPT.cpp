/*
 * ZDevicesPT.cpp
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include "ZDevicesPT.h"

namespace zigbee {
  namespace http {

    ZDevicesPT::ZDevicesPT(std::shared_ptr<ZDevices> zDevices) noexcept {
        for (const auto &device : zDevices->getDevices()) {
            BOOST_LOG_TRIVIAL(info) << device.getNwkAddr();
            if (!device.getEndpoints().empty()) {
                add(boost::lexical_cast<std::string>(device.getNwkAddr()), device.getExtAddr());
            }
        }
    }
  } /* namespace http */
} /* namespace zigbee */
