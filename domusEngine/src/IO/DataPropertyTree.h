/*
 * DataPropertyTree.h
 *
 *  Created on: 02/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_IO_DATAPROPERTYTREE_H_
#define SRC_IO_DATAPROPERTYTREE_H_

#include <boost/property_tree/ptree.hpp>

namespace zigbee {

class DataPropertyTree : public boost::property_tree::ptree {
public:
	DataPropertyTree(const std::vector<uint8_t> & data);
	virtual ~DataPropertyTree();
};

} /* namespace zigbee */

#endif /* SRC_IO_DATAPROPERTYTREE_H_ */
