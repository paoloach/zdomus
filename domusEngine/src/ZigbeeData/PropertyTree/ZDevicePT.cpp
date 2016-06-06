/*
 * ZDevicePT.cpp
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#include <boost/lexical_cast.hpp>

#include "ZDevicePT.h"

namespace zigbee {

  using boost::property_tree::ptree;

  ZDevicePT::ZDevicePT(const ZDevice &zDevice) noexcept {
      ptree endpoints;

      add("extended_address", zDevice.getExtAddr());
      add("short_address", zDevice.getNwkAddr());
      add("capability", zDevice.getCapabilities());
      int index = 0;
      if (!zDevice.getEndpoints().empty()) {
          for (auto endpoint : zDevice.getEndpoints()) {
              endpoints.add(boost::lexical_cast<std::string>(index), boost::lexical_cast<std::string>(endpoint.first));
              index++;
          }
          push_back({"endpoints", endpoints});
      }
  }
} /* namespace zigbee */
