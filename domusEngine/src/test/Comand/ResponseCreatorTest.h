/*
 * ResponseCreatorTest.h
 *
 *  Created on: 21/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_RESPONSECREATORTEST_H_
#define SRC_TEST_COMAND_RESPONSECREATORTEST_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../Comand/ResponseCreator.h"
#include "../Mocks/ComandMock.h"


namespace zigbee {
namespace test {

class ResponseCreatorTest : public ::testing::Test{
public:
	virtual ~ResponseCreatorTest();
protected:
	virtual void SetUp();
	virtual void TearDown();
protected:
	std::shared_ptr<ResponseCreator> responseCreator;

	std::shared_ptr<ComandMock> comand1;
	std::shared_ptr<ComandMock> comand2;

	std::vector<Comand_P > comands;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_COMAND_RESPONSECREATORTEST_H_ */
