/*
 * CmdSendCmdTest.h
 *
 *  Created on: 12/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_COMAND_CMDSENDCMDTEST_H_
#define SRC_TEST_COMAND_CMDSENDCMDTEST_H_

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../ZigbeeData/ZDevices.h"
#include "../../Comand/CmdSendCmd.h"
#include "../Mocks/ZigbeeDeviceMock.h"

namespace zigbee {
namespace test {

class CmdSendCmdTest : public ::testing::Test {
public:
	virtual ~CmdSendCmdTest();
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	CmdSendCmd * cmdSendCmd;
	std::string inputJson;
	ZigbeeDeviceMock zigbeeDevice;
private:
	std::string createInputJSON(NwkAddr nwkAddr,EndpointID endpoint, ClusterID cluster, int commandId, const std::vector<uint8_t> & data);
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_COMAND_CMDSENDCMDTEST_H_ */
