/*
 * properyTreeUtils.cpp
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/lexical_cast.hpp>

#include "jsonFields.h"

#include "ProperyTreeUtils.h"


namespace zigbee {

using boost::property_tree::ptree;

void ProperyTreeUtils::write(ptree & properties, const std::vector<uint8_t> & data) {
	ptree propertiesData {};

	for(const uint8_t & value: data){
		ptree propertyValue {boost::lexical_cast<std::string>((int)value)};
		propertiesData.push_back({DATA_VALUE_NAME, propertyValue});
	}

	properties.put_child(DATA_NAME, propertiesData);

}
void ProperyTreeUtils::read(ptree & properties,  std::vector<uint8_t> & data){
	ptree propertiesData =  properties.get_child(DATA_NAME);
	for(auto property: propertiesData){
		data.push_back( boost::lexical_cast<int>( property.second.data()));
	}
}
} /* namespace zigbee */
