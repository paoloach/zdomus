/*
 * ZDevicePT.cpp
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "ZDevicePT.h"

namespace zigbee {

  using boost::property_tree::ptree;

  ZDevicePT::ZDevicePT(ZDevice * zDevice) noexcept {
      ptree endpoints;

      add("extended_address", zDevice->getExtAddr());
      add("short_address", zDevice->getNwkAddr().getId());
      add("capability", zDevice->getCapabilities());
      int index = 0;
      if (!zDevice->getEndpoints().empty()) {
          for (auto endpoint : zDevice->getEndpoints()) {
              endpoints.add(std::to_string(index), boost::lexical_cast<std::string>(endpoint.first));
              index++;
          }
          push_back({"endpoints", endpoints});
      }
      std::stringstream stream;
      boost::property_tree::json_parser::write_json(stream, *this, false);
      BOOST_LOG_TRIVIAL(info) << "response: " << stream.str();
  }
} /* namespace zigbee */
