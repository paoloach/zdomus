/*
 * AttributePT.h
 *
 *  Created on: 26/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_PROPERTYTREE_ATTRIBUTEPT_H_
#define SRC_ZIGBEEDATA_PROPERTYTREE_ATTRIBUTEPT_H_

#include <boost/property_tree/ptree.hpp>
#include <memory>

namespace zigbee {

class ZCLAttribute;

class AttributePT : public boost::property_tree::ptree {
public:
	AttributePT(const std::shared_ptr<ZCLAttribute> & cluster);
};

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_PROPERTYTREE_ATTRIBUTEPT_H_ */
