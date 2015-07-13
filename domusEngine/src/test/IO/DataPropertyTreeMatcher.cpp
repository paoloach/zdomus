/*
 * DataPropertyTreeMatcher.cpp
 *
 *  Created on: 02/dic/2014
 *      Author: Paolo Achdjian
 */


#include <algorithm>

#include "jsonFields.h"
#include "boost/lexical_cast.hpp"
#include "DataPropertyTreeMatcher.h"



namespace zigbee {

using namespace testing;

DataPropertyTreeMatcher::DataPropertyTreeMatcher(const std::vector<uint8_t> & data) :
		data(data) {

}

DataPropertyTreeMatcher::DataPropertyTreeMatcher(const uint8_t * dataOrig, int len) {
	for(int i=0; i < len; i++){
		data.push_back(dataOrig[i]);
	}
}

DataPropertyTreeMatcher::~DataPropertyTreeMatcher() {
}

bool DataPropertyTreeMatcher::MatchAndExplain(boost::property_tree::ptree dataProperty, testing::MatchResultListener* listener) const {
	if (dataProperty.size() != data.size()){
		*listener << "different size: expected " << data.size() << " but got " << dataProperty.size();
		return false;
	}

	auto  dataIter = data.begin();

	for (const auto & dataValue: dataProperty){
		if (dataValue.first != DATA_VALUE_NAME){
			*listener << "expected " << DATA_VALUE_NAME << " but got " << dataValue.first;
			return false;
		}
		int dataV = boost::lexical_cast<int>(dataValue.second.data());

		if (dataV != *dataIter){
			*listener << "expected " << *dataIter << " but got " << dataV;
			return false;
		}
		dataIter++;
	}
	return true;
}

void DataPropertyTreeMatcher::DescribeTo(::std::ostream* os) const {
	*os << "data matcher";
}


} /* namespace zigbee */
