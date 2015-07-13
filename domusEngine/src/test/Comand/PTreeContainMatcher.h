/*
 * PTreeContainMatcher.h
 *
 *  Created on: 21/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_PTREECONTAINMATCHER_H_
#define SRC_TEST_COMAND_PTREECONTAINMATCHER_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <boost/property_tree/ptree.hpp>
#include <string>

namespace zigbee {
namespace test {

class PTreeContainMatcher: public testing::MatcherInterface<const boost::property_tree::ptree &> {
public:
	PTreeContainMatcher(const boost::property_tree::ptree & properties) :
			properties(properties) {
	}

	virtual bool MatchAndExplain(const boost::property_tree::ptree& containing, testing::MatchResultListener* listener) const {
		for (auto property: properties){
			if (containing.count(property.first) == 0){
				(*listener) << "Property " << property.first << " is absent";
				return false;
			}
		}
		return true;
	}

	virtual void DescribeTo(::std::ostream* ) const {
	}


private:
	const boost::property_tree::ptree properties;
	std::string propertyAbsent;
};

inline  testing::Matcher<const boost::property_tree::ptree & > contains(const boost::property_tree::ptree & properties){
	return MakeMatcher(new PTreeContainMatcher{properties});
}

}
}

#endif /* SRC_TEST_COMAND_PTREECONTAINMATCHER_H_ */
