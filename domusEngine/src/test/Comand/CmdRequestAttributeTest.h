/*
 * CmdRequestAttributeTest.h
 *
 *  Created on: 13/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_CMDREQUESTATTRIBUTETEST_H_
#define SRC_TEST_COMAND_CMDREQUESTATTRIBUTETEST_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../Comand/CmdRequestAttribute.h"
#include "../Mocks/ZigbeeDeviceMock.h"

namespace zigbee {
namespace test {

class CmdRequestAttributeTest : public ::testing::Test{
public:
	virtual ~CmdRequestAttributeTest();
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	CmdRequestAttribute * cmdReqAttribute;
	std::string inputJson;
	ZigbeeDeviceMock zigbeeDevice;
private:
	std::string createInputJSON(NwkAddr nwkAddr,EndpointID endpoint, ClusterID cluster, int attributeId);
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_COMAND_CMDREQUESTATTRIBUTETEST_H_ */
