/*
 * InvalidZEndpointException.cpp
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include "InvalidZEndpointException.h"

namespace zigbee {

  InvalidZEndpointException::InvalidZEndpointException(NwkAddr nwkAddress, EndpointID endpoint) {
      std::stringstream stream{};
      stream << "The endpoint " << endpoint << " doesn't exist on device " << nwkAddress;
      message = stream.str();
  }


} /* namespace zigbee */
