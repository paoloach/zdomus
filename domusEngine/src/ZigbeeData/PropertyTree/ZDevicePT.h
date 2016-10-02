/*
 * ZDevicePT.h
 *
 *  Created on: 23/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_PROPERTYTREE_ZDEVICEPT_H_
#define SRC_ZIGBEEDATA_PROPERTYTREE_ZDEVICEPT_H_

#include <boost/property_tree/ptree.hpp>
#include "../ZDevice.h"

namespace zigbee {

  class ZDevicePT : public boost::property_tree::ptree {
  public:
      ZDevicePT(ZDevice* zDevice) noexcept;

      virtual ~ZDevicePT() noexcept=default;
  };

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_PROPERTYTREE_ZDEVICEPT_H_ */
