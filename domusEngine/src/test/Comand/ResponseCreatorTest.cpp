/*
 * ResponseCreatorTest.cpp
 *
 *  Created on: 21/dic/2014
 *      Author: Paolo Achdjian
 */

#include "ResponseCreatorTest.h"

#include "../Mocks/ComandMock.h"

namespace zigbee {
namespace test {

using namespace testing;

ResponseCreatorTest::~ResponseCreatorTest() {
}

void ResponseCreatorTest::SetUp(){
	responseCreator = std::make_shared<ResponseCreator>();

	comand1 = std::make_shared<ComandMock>();
	comand2 = std::make_shared<ComandMock>();

	comands.push_back(std::dynamic_pointer_cast<Comand>(comand1));
	comands.push_back(std::dynamic_pointer_cast<Comand>(comand2));
}
void ResponseCreatorTest::TearDown(){

}

TEST_F( ResponseCreatorTest, execute_and_getResponses) {
	EXPECT_CALL(*(comand1.get()), execute());
	EXPECT_CALL(*(comand2.get()), execute());
	EXPECT_CALL(*(comand1.get()), getResponse(_));
	EXPECT_CALL(*(comand2.get()), getResponse(_));

	responseCreator->generateResponse(comands);


}

} /* namespace test */
} /* namespace zigbee */
