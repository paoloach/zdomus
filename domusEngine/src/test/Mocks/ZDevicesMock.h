/*
 * ZDevicesMock.h
 *
 *  Created on: 05/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZDEVICESMOCK_H_
#define SRC_TEST_MOCKS_ZDEVICESMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../ZigbeeData/ZDevices.h"
#include "shared_ptr_mock.h"

namespace zigbee {
namespace test {

class ZDevicesMock: public ZDevices, public sharedMockClass<ZDevices, ZDevicesMock> {
public:
	ZDevicesMock();
	virtual ~ZDevicesMock();

	MOCK_METHOD1(getDifferences, boost::property_tree::ptree (uint32_t ));
	MOCK_METHOD1(put, void (const AnnunceMessage & ));
	MOCK_METHOD1(put, void (const SimpleDescMessage & ));
	MOCK_CONST_METHOD0(getNumDevices, int ());
	MOCK_METHOD0(getDevices, std::vector<ZDevice *> ());
	MOCK_CONST_METHOD1(getDevice, ZDevice * (const ExtAddress & extAddress));
	MOCK_CONST_METHOD1(getDevice, ZDevice * (NwkAddr nwkAddr));
	MOCK_CONST_METHOD1(exists, bool (const ExtAddress & extAddress));
};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZDEVICESMOCK_H_ */
