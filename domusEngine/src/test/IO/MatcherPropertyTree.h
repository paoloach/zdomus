/*
 * MatcherPropertyTree.h
 *
 *  Created on: 02/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_IO_MATCHERPROPERTYTREE_H_
#define SRC_TEST_IO_MATCHERPROPERTYTREE_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <boost/property_tree/ptree.hpp>
#include <zigbee/messageStructure/ReadAttributeResponseMessage.h>

namespace zigbee {

class MatcherPropertyTree  : public testing::MatcherInterface<boost::property_tree::ptree> {
public:
	MatcherPropertyTree(const ReadAttributeResponseMessage & attributeMessage);
	virtual ~MatcherPropertyTree();
private:
	ReadAttributeResponseMessage attributeMessage;
protected:
	virtual bool MatchAndExplain(boost::property_tree::ptree x, testing::MatchResultListener* listener) const;
	virtual void DescribeTo(::std::ostream* os) const;
};


inline testing::Matcher<boost::property_tree::ptree> isAttributeResponseMessage(const ReadAttributeResponseMessage & attributeMessage) {
	return testing::MakeMatcher(new MatcherPropertyTree { attributeMessage });
}

} /* namespace zigbee */

#endif /* SRC_TEST_IO_MATCHERPROPERTYTREE_H_ */
