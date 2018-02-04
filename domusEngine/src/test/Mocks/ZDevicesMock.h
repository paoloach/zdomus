/*
 * ZDevicesMock.h
 *
 *  Created on: 05/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZDEVICESMOCK_H_
#define SRC_TEST_MOCKS_ZDEVICESMOCK_H_

#include <gtest/gtest.h>
#include "../../ZigbeeData/ZDevices.h"
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

namespace zigbee {
namespace test {

class ZDevicesMock: public ZDevices {
public:
	ZDevicesMock();
	virtual ~ZDevicesMock();

    MAKE_MOCK1(put, void (const AnnunceMessage & ));
    MAKE_MOCK1(put, void (const SimpleDescMessage & ));
    MAKE_MOCK1(put, void (const ZEndpoint & ));
    MAKE_MOCK1(put, void (const BindResponse & ));
    MAKE_MOCK1(addDeviceInfo,  void (const IEEEAddressResponse &ieeeAddressResponse));
    MAKE_MOCK1(getDifferences, boost::property_tree::ptree (uint32_t token));

    MAKE_CONST_MOCK0(getNumDevices, int ());

    MAKE_MOCK0(getDevices, std::vector<ZDevice *> ());

    MAKE_CONST_MOCK1(getDevice, ZDevice *(const ExtAddress &extAddress) );

    MAKE_CONST_MOCK1(getDevice, ZDevice *(NwkAddr nwkAddress) );

    MAKE_CONST_MOCK1(getDeviceNoExcept, ZDevice *(NwkAddr nwkAddress) );

    MAKE_CONST_MOCK1(exists, bool (const ExtAddress &extAddress) );

    MAKE_MOCK1(addObserver, void (Observer observer));

    MAKE_MOCK1(removeObserver, void (Observer observer));

};


} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZDEVICESMOCK_H_ */
