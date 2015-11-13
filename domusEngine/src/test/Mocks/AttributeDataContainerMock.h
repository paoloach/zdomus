/*
 * AttributeDataContainerMock.h
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ATTRIBUTEDATACONTAINERMOCK_H_
#define SRC_TEST_MOCKS_ATTRIBUTEDATACONTAINERMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../IO/AttributeDataContainer.h"

namespace zigbee {
namespace test {

class AttributeDataContainerMock: public AttributeDataContainer {
public:
	AttributeDataContainerMock();
	virtual ~AttributeDataContainerMock();
public:
	MOCK_METHOD1(push, void (const AttributeData & attribute));
	MOCK_METHOD1(get, boost::property_tree::ptree (uint64_t token));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ATTRIBUTEDATACONTAINERMOCK_H_ */
