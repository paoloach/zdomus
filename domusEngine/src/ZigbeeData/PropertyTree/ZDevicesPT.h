/*
 * ZDevicesPT.h
 *
 *  Created on: 24/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_PROPERTYTREE_ZDEVICESPT_H_
#define SRC_ZIGBEEDATA_PROPERTYTREE_ZDEVICESPT_H_

#include <boost/property_tree/ptree.hpp>
#include "../ZDevices.h"

namespace zigbee {
    namespace http {

        class ZDevicesPT : public boost::property_tree::ptree {
        public:
            ZDevicesPT(std::shared_ptr<ZDevices> zDevices) noexcept;
            virtual ~ZDevicesPT() noexcept= default;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_PROPERTYTREE_ZDEVICESPT_H_ */
