/*
 * ZDevicesPT.cpp
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <boost/property_tree/json_parser.hpp>
#include "ZDevicesPT.h"

namespace zigbee {
  namespace http {

    ZDevicesPT::ZDevicesPT(ZDevices * zDevices) noexcept {
        for (const auto &device : zDevices->getDevices()) {
            if (!device->getEndpoints().empty()) {
                std::stringstream stream;
                add(boost::lexical_cast<std::string>(device->getNwkAddr()), device->getExtAddr());
            }
        }
        std::stringstream stream;
        boost::property_tree::json_parser::write_json(stream, *this, false);
        BOOST_LOG_TRIVIAL(trace) << "response: " << stream.str();
    }
  } /* namespace http */
} /* namespace zigbee */
