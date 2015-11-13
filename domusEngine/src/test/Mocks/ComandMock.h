/*
 * ComandMock.h
 *
 *  Created on: 21/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_COMANDMOCK_H_
#define SRC_TEST_MOCKS_COMANDMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../Comand/Comand.h"

namespace zigbee {
namespace test {

class ComandMock :public Comand{
public:
	ComandMock();
	virtual ~ComandMock();

	MOCK_METHOD1(parseData, bool (const std::string &line));

	MOCK_METHOD0(execute, void ());
	MOCK_METHOD1(getResponse, void (boost::property_tree::ptree & result));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_COMANDMOCK_H_ */
