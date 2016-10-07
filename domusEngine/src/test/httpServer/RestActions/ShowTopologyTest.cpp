//
// Created by paolo on 06/10/16.
//

#include "ShowTopologyTest.h"

#include "../../../httpServer/RestActions/ShowTopology.h"
using std::make_unique;
using namespace testing;
using zigbee::NwkAddr;
using std::endl;
using namespace Json;

namespace zigbee {
    namespace http {
        namespace test {

            static ExtAddress rootAddr = {0x10,0x23,034,0x43,0x23,0x44,0x54};
            static ExtAddress child1_1Addr = {0x10,0x23,034,0x43,0x23,0x44,0x55};
            static ExtAddress child2_1Addr = {0x10,0x23,034,0x43,0x23,0x44,0x56};
            static ExtAddress child2_2Addr = {0x10,0x23,034,0x43,0x23,0x44,0x57};
            static NwkAddr nwkRootAdr{0};
            static NwkAddr nwkChild1_1Adr{10};
            static NwkAddr nwkChild2_1Adr{20};
            static NwkAddr nwkChild2_2Adr{21};
            static std::set<NwkAddr> rootChildren = {nwkChild1_1Adr};
            static std::set<NwkAddr> Children1 = {nwkChild2_1Adr, nwkChild2_2Adr};
            static ZDevice root{rootAddr, NwkAddr{0}, rootChildren};
            static ZDevice child1_1{child1_1Addr, nwkChild1_1Adr, Children1};
            static ZDevice child2_1{child2_1Addr, nwkChild2_1Adr, std::set<NwkAddr>()};
            static ZDevice child2_2{child2_2Addr, nwkChild2_2Adr, std::set<NwkAddr>()};



            void ShowTopologyTest::SetUp() {
                singletonObject = make_unique<SingletonObjectsMock>();
                zDevices = make_unique<zigbee::test::ZDevicesMock>();

                EXPECT_CALL(*singletonObject, getZDevices()).Times(AtLeast(1)).WillRepeatedly(Return(zDevices.get()));
                EXPECT_CALL(*zDevices, getDeviceNoExcept(nwkRootAdr)).WillOnce(Return(&root));
                EXPECT_CALL(*zDevices, getDeviceNoExcept(nwkChild1_1Adr)).WillOnce(Return(&child1_1));
                EXPECT_CALL(*zDevices, getDeviceNoExcept(nwkChild2_1Adr)).WillOnce(Return(&child2_1));
                EXPECT_CALL(*zDevices, getDeviceNoExcept(nwkChild2_2Adr)).WillOnce(Return(&child2_2));


                showTopology = make_unique<ShowTopology>(*singletonObject);
            }

            void ShowTopologyTest::TearDown() {
                zDevices.reset();
                showTopology.reset();
                singletonObject.reset();
            }


            TEST_F(ShowTopologyTest, rightTopology) {
                std::stringstream outStream;
                EXPECT_CALL(response, send()).Times(1).WillOnce(ReturnRef(outStream));
                ServerRequest serverRequest(request);
                (*showTopology)(PlaceHolders(), serverRequest, response);

                std::cout << outStream.str() << std::endl;
                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                Json::Value root(objectValue);
                outStream >> root;

                ASSERT_THAT(root["nwkId"] ,0);
                ASSERT_THAT(root["ieeeAddress"] ,rootAddr.asString());
                auto rootChildren = root["children"];
                ASSERT_THAT(rootChildren.size(), 1);
                auto chil1 = rootChildren[0];
                ASSERT_THAT(chil1["nwkId"] ,nwkChild1_1Adr.getId());
                ASSERT_THAT(chil1["ieeeAddress"] ,child1_1Addr.asString());
                auto child1Children = chil1["children"];

                ASSERT_THAT(child1Children.size(), 2);
                auto chil2_1 = child1Children[0];
                ASSERT_THAT(chil2_1["nwkId"] ,nwkChild2_1Adr.getId());
                ASSERT_THAT(chil2_1["ieeeAddress"] ,child2_1Addr.asString());

                auto chil2_2 = child1Children[1];
                ASSERT_THAT(chil2_2["nwkId"] ,nwkChild2_2Adr.getId());
                ASSERT_THAT(chil2_2["ieeeAddress"] ,child2_2Addr.asString());
            }

        }
    }
}