/*
 * DataPropertyTree.cpp
 *
 *  Created on: 02/dic/2014
 *      Author: Paolo Achdjian
 */

#include "DataPropertyTree.h"
#include "jsonFields.h"

namespace zigbee {

DataPropertyTree::DataPropertyTree(const std::vector<uint8_t> & data_) {
	for (const uint8_t & value : data_) {
		add(DATA_VALUE_NAME, value);
	}
}

DataPropertyTree::~DataPropertyTree() {
}

} /* namespace zigbee */
