/*
 * AttributeDataContainer.h
 *
 *  Created on: 01/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_IO_ATTRIBUTEDATACONTAINER_H_
#define SRC_IO_ATTRIBUTEDATACONTAINER_H_

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <deque>

#include "../ZigbeeData/AttributeData.h"
namespace zigbee {

class AttributeDataContainer {
public:
	AttributeDataContainer(unsigned int maxElements);
	virtual ~AttributeDataContainer();
public:
	virtual void push(const AttributeData & attribute);
	virtual boost::property_tree::ptree get(uint64_t token);
private:
	class Data {
	public:
		AttributeData attribute;
		uint64_t tokenUpdate;
	};

	boost::property_tree::ptree getPropery(const zigbee::AttributeData& dataattribute);
private:
	unsigned int maxElements;
	uint64_t tokenUpdate;
	std::deque<Data> attributes;
};

} /* namespace zigbee */

#endif /* SRC_IO_ATTRIBUTEDATACONTAINER_H_ */
