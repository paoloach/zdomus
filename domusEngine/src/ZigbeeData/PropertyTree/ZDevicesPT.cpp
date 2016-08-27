/*
 * ZDevicesPT.cpp
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include "ZDevicesPT.h"

namespace zigbee {
  namespace http {

    ZDevicesPT::ZDevicesPT(std::shared_ptr<ZDevices> zDevices) noexcept {
        for (const auto &device : zDevices->getDevices()) {
            if (!device.getEndpoints().empty()) {
                std::stringstream stream;
                stream << "network address: " << std::hex << device.getNwkAddr();
                BOOST_LOG_TRIVIAL(info) << stream.str();
                add(boost::lexical_cast<std::string>(device.getNwkAddr()), device.getExtAddr());
            }
        }
    }
  } /* namespace http */
} /* namespace zigbee */
