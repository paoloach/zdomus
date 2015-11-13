/*
 * DataPropertyTreeMatcher.h
 *
 *  Created on: 02/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_IO_DATAPROPERTYTREEMATCHER_H_
#define SRC_TEST_IO_DATAPROPERTYTREEMATCHER_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/property_tree/ptree.hpp>

namespace zigbee {

class DataPropertyTreeMatcher: public testing::MatcherInterface<boost::property_tree::ptree> {
public:
	DataPropertyTreeMatcher(const std::vector<uint8_t> & data);
	DataPropertyTreeMatcher(const uint8_t * data, int len);
	virtual ~DataPropertyTreeMatcher();
private:
	std::vector<uint8_t> data;
public:
	virtual bool MatchAndExplain(boost::property_tree::ptree x, testing::MatchResultListener* listener) const;
	virtual void DescribeTo(::std::ostream* os) const;
};

inline testing::Matcher<boost::property_tree::ptree> isDataPropery(const std::vector<uint8_t> & data) {
	return testing::MakeMatcher(new DataPropertyTreeMatcher { data });
}

inline testing::Matcher<boost::property_tree::ptree> isDataPropery(const uint8_t * data, int len) {
	return testing::MakeMatcher(new DataPropertyTreeMatcher { data,len });
}

} /* namespace zigbee */

#endif /* SRC_TEST_IO_DATAPROPERTYTREEMATCHER_H_ */
