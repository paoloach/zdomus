/*
 * MatcherPropertyTree.cpp
 *
 *  Created on: 02/dic/2014
 *      Author: Paolo Achdjian
 */

#include "jsonFields.h"
#include "MatcherPropertyTree.h"
#include "DataPropertyTreeMatcher.h"

namespace zigbee {

MatcherPropertyTree::MatcherPropertyTree(const ReadAttributeResponseMessage & attributeMessage) : attributeMessage(attributeMessage){

}

MatcherPropertyTree::~MatcherPropertyTree() {
}

bool MatcherPropertyTree::MatchAndExplain(boost::property_tree::ptree dataProperty, testing::MatchResultListener* listener) const {
	if (dataProperty.size() != 8){
		*listener << "different size: expected 8  but got " << dataProperty.size();
		return false;
	}

	if (dataProperty.get<int>(ATTR_ID_NAME) != attributeMessage.attrID){
		*listener << "different attribute id: expected " << (int)attributeMessage.attrID << " but got " << dataProperty.get<int>(ATTR_ID_NAME);
		return false;
	}

	if (dataProperty.get<int>(CLUSTER_ID_NAME) != attributeMessage.clusterId){
		*listener << "different cluster id: expected " << (int)attributeMessage.clusterId << " but got " << dataProperty.get<int>(CLUSTER_ID_NAME);
		return false;
	}
	if (dataProperty.get<int>(ENDPOINT_ID_NAME) != attributeMessage.endpoint){
		*listener << "different endpoint: expected " << (int)attributeMessage.endpoint << " but got " << dataProperty.get<int>(ENDPOINT_ID_NAME);
		return false;
	}
	if (dataProperty.get<int>(SHORT_ADDR_NAME) != attributeMessage.networkAddr){
		*listener << "different network address: expected " << (int)attributeMessage.networkAddr << " but got " << dataProperty.get<int>(SHORT_ADDR_NAME);
		return false;
	}
	if (dataProperty.get<int>(PAN_ID_NAME) != attributeMessage.panId){
		*listener << "different pan id: expected " << (int)attributeMessage.panId << " but got " << dataProperty.get<int>(PAN_ID_NAME);
		return false;
	}
	if (dataProperty.get<int>(STATUS_NAME) != attributeMessage.status){
		*listener << "different status: expected " << (int)attributeMessage.status << " but got " << dataProperty.get<int>(STATUS_NAME);
		return false;
	}
	if (dataProperty.get<int>(TYPE_NAME) != attributeMessage.type){
		*listener << "different type id: expected " << (int)attributeMessage.type << " but got " << dataProperty.get<int>(TYPE_NAME);
		return false;
	}

	DataPropertyTreeMatcher matcher(attributeMessage.data, attributeMessage.dataLen);

	return matcher.MatchAndExplain(dataProperty.get_child(DATA_NAME), listener);
}

void MatcherPropertyTree::DescribeTo(::std::ostream* os) const {
	*os << "data matcher";
}

} /* namespace zigbee */
