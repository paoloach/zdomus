//
// Created by paolo on 02/01/17.
//

#include "IEEEAddressResponseSerialExecutorTest.h"

namespace zigbee {
    namespace test {
        using std::string;
        using trompeloeil::_;
        static ExtAddress expectedExtAddress = {0x01, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x33};
        static NwkAddr expectedNwkAddr{0x3456};
        static NwkAddr expectedChild1{0x343};
        static NwkAddr expectedChild2{0x123};

        void IEEEAddressResponseSerialExecutorTest::SetUp() {
            Test::SetUp();

            getZDevices = NAMED_ALLOW_CALL(singletonObjectsMock, getZDevices()).RETURN(&zDevicesMock);

            executor = std::make_unique<IEEEAddressResponseSerialExecutor>(&singletonObjectsMock);
        }

        void IEEEAddressResponseSerialExecutorTest::TearDown() {
            Test::TearDown();
            executor.release();
            getZDevices.release();
        }


        TEST_F(IEEEAddressResponseSerialExecutorTest, ZeroChild) {
            IEEEAddrResp expectedRequest;

            REQUIRE_CALL(zDevicesMock, addDeviceInfo(_))
                .WITH(_1.ieeeAddr == expectedExtAddress)
                .WITH(_1.nwkAddr == expectedNwkAddr)
                .WITH(_1.children.size() == 0);

            executor->operator()("IE: 01-0a-0b-0c-0d-0e-0f-33, 3456, 0\n");

        }

        TEST_F(IEEEAddressResponseSerialExecutorTest, 2Children) {
            IEEEAddrResp expectedRequest;

            REQUIRE_CALL(zDevicesMock, addDeviceInfo(_))
                .WITH(_1.ieeeAddr == expectedExtAddress)
                .WITH(_1.nwkAddr == expectedNwkAddr)
                .WITH(_1.children.size() == 2)
                .WITH(_1.children.count(expectedChild1) > 0)
                .WITH(_1.children.count(expectedChild2) > 0);

            executor->operator()("IE: 01-0a-0b-0c-0d-0e-0f-33, 3456, 2, 0343, 0123\n");

        }
    }

}
