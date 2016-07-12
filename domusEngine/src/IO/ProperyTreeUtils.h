/*
 * properyTreeUtils.h
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_IO_PROPERYTREEUTILS_H_
#define SRC_IO_PROPERYTREEUTILS_H_

#include <boost/property_tree/ptree.hpp>
#include <vector>

namespace zigbee {

class ProperyTreeUtils {
public:
	static void write(boost::property_tree::ptree & ptree, const std::vector<uint8_t> & data);
	static void read(boost::property_tree::ptree & ptree,  std::vector<uint8_t> & data);
};

} /* namespace zigbee */

#endif /* SRC_IO_PROPERYTREEUTILS_H_ */
