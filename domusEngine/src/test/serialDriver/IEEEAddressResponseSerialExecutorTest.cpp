//
// Created by paolo on 02/01/17.
//

#include "IEEEAddressResponseSerialExecutorTest.h"

namespace zigbee {
    namespace test {
        using namespace testing;
        using std::string;
        static ExtAddress expectedExtAddress = {0x01, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x33};
        static NwkAddr expectedNwkAddr{0x3456};
        static NwkAddr expectedChild1{0x343};
        static NwkAddr expectedChild2{0x123};

        MATCHER_P2(HasZeroChild, expextedExtAddr, expectedNwkId, "zero child message") {
            return arg.ieeeAddr == expextedExtAddr && arg.nwkAddr == expectedNwkId && arg.children.size() == 0;
        }

        MATCHER_P4(Has2Children, expextedExtAddr, expectedNwkId, child1, child2, "message has 2 children") {
            return arg.ieeeAddr == expextedExtAddr && arg.nwkAddr == expectedNwkId && arg.children.size() == 2 && arg.children.count(child1) > 0 && arg.children.count(child2) > 0;
        }

        void IEEEAddressResponseSerialExecutorTest::SetUp() {
            Test::SetUp();

            EXPECT_CALL(singletonObjectsMock, getZDevices()).WillOnce(Return(&zDevicesMock));

            executor = std::make_unique<IEEEAddressResponseSerialExecutor>(&singletonObjectsMock);
        }

        void IEEEAddressResponseSerialExecutorTest::TearDown() {
            Test::TearDown();
            executor.reset();
        }


        TEST_F(IEEEAddressResponseSerialExecutorTest, ZeroChild) {
            IEEEAddrResp expectedRequest;

            EXPECT_CALL(zDevicesMock, addDeviceInfo(HasZeroChild(expectedExtAddress, expectedNwkAddr)));

            executor->operator()("IE: 01-0a-0b-0c-0d-0e-0f-33, 3456, 0\n");

        }

        TEST_F(IEEEAddressResponseSerialExecutorTest, 2Children) {
            IEEEAddrResp expectedRequest;

            EXPECT_CALL(zDevicesMock, addDeviceInfo(Has2Children(expectedExtAddress, expectedNwkAddr, expectedChild1, expectedChild2)));

            executor->operator()("IE: 01-0a-0b-0c-0d-0e-0f-33, 3456, 2, 0343, 0123\n");

        }
    }

}
