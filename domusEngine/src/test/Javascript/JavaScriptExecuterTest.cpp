/*
 * JavaScriptExecuterTest.cpp
 *
 *  Created on: 31/dic/2014
 *      Author: Paolo Achdjian
 */

#include <sstream>
#include <zcl/attributeTypes/ZCLuint16Attribute.h>
#include <zcl/clusterTypes/BasicCluster.h>

#include "JavaScriptExecuterTest.h"


namespace zigbee {
    namespace test {

        using std::make_shared;
        using std::make_unique;
        using namespace testing;
        using namespace boost::posix_time;
        using std::string;

        static std::string EXTENDED_ADDRESS = "00-01-02-03-04-05-06-07";
        static constexpr NwkAddr NWK_ADDRESS{10};
        static constexpr EndpointID ENDPOINT_ID{23};
        static constexpr ClusterID CLUSTER_ID{1};
        static constexpr uint32_t PROFILE_ID{11};
        static constexpr uint32_t DEVICE_ID{12};
        static constexpr uint32_t DEVICE_VER{13};
        static const std::vector<ClusterID> IN_CLUSTERS{BasicClusterID, PowerConfigurationClusterID};
        static const std::vector<ClusterID> OUT_CLUSTERS{ClusterID{3}, ClusterID{4}};

        static constexpr uint32_t ATTRIBUTE0_ID{0};
        static constexpr uint32_t APPLICATION_VERSION_ID = 1;

        void JavaScriptExecuterTest::SetUp() {
            zDevices = std::make_unique<ZDevicesMock>();
            zigbeeDevice = make_unique<ZigbeeDeviceMock>();
            extAddress = convertFromString(EXTENDED_ADDRESS);
            restHandler = make_unique<http::RestHandlerMock>(singletonObjects);
            EXPECT_CALL(singletonObjects, getClusters()).Times(AnyNumber()).WillRepeatedly(Return(&clustersMock));
            EXPECT_CALL(singletonObjects, getZigbeeDevice()).Times(AnyNumber()).WillRepeatedly(Return(zigbeeDevice.get()));
            EXPECT_CALL(singletonObjects, getZDevices()).Times(AnyNumber()).WillRepeatedly(Return(zDevices.get()));
            EXPECT_CALL(singletonObjects, getRestHandler()).Times(AnyNumber()).WillRepeatedly(Return(restHandler.get()));
        }

        void JavaScriptExecuterTest::TearDown() {
            zDevices.reset();
            zigbeeDevice.reset();
        }

        ExtAddress JavaScriptExecuterTest::convertFromString(const std::string &strExt) {
            ExtAddress extAddress{};
            std::stringstream stream{strExt};
            stream >> extAddress;
            return extAddress;
        }

        TEST_F(JavaScriptExecuterTest, constructor_descructor)  {
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(10));

            jsExecuter.reset();
        }

        TEST_F(JavaScriptExecuterTest, executing_simple_script) {
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(10));

            jsExecuter->run("a=3;");
            jsExecuter->join();

            jsExecuter.reset();
        }

        TEST_F(JavaScriptExecuterTest, creating_attribute_ZCL_uint8) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream js;
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(10));
            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            std::shared_ptr<Cluster> cluster(new BasicCluster(zigbeeDevice.get(), ENDPOINT_ID, NWK_ADDRESS));
            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, ClusterID(BASIC_CLUSTER))).WillOnce(Return(cluster));

            string objectName = "Z" + ZCL_uint8_Attribute::name();

            js << objectName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << std::dec << BASIC_CLUSTER << "," << APPLICATION_VERSION_ID << ");";

            jsExecuter->run(js.str());
            sleep(1);
            jsExecuter->join();

            jsExecuter.reset();
        }


        TEST_F(JavaScriptExecuterTest, creating_attribute_ZCL_uint8_log_type) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream js;
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(10));
            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            std::shared_ptr<Cluster> cluster(new BasicCluster(zigbeeDevice.get(), ENDPOINT_ID, NWK_ADDRESS));
            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, ClusterID(BASIC_CLUSTER))).WillOnce(Return(cluster));

            string objectName = "Z" + ZCL_uint8_Attribute::name();

            js << "var a = " << objectName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << BASIC_CLUSTER << "," << APPLICATION_VERSION_ID << ");";
            js << "var log = Log();";
            js << "log.info(a);";

            jsExecuter->run(js.str());
            sleep(1);
            jsExecuter->join();
            jsExecuter.reset();
        }

        TEST_F(JavaScriptExecuterTest, creating_attribute_ZCL_uint8_log_type_two_time) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream js;
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(2));
            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            std::shared_ptr<Cluster> cluster(new BasicCluster(zigbeeDevice.get(), ENDPOINT_ID, NWK_ADDRESS));
            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, ClusterID(BASIC_CLUSTER))).WillOnce(Return(cluster));

            string objectName = "Z" + ZCL_uint8_Attribute::name();

            js << "var log = Log();";
            js << "if (a == null){";
            js << "  var a = " << objectName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << BASIC_CLUSTER << "," << APPLICATION_VERSION_ID << ");";
            js << "} else {";
            js << "  log.info(a);";
            js << "};";

            jsExecuter->run(js.str());
            sleep(5);
            jsExecuter->join();

            jsExecuter.reset();
        }


        TEST_F(JavaScriptExecuterTest, creating_invalid_attribute_ZCL_uint16) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream js;
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(10));
            EXPECT_CALL(*zDevices, exists(extAddress)).WillOnce(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillOnce(Return(&zDevice));
            std::shared_ptr<Cluster> cluster(new BasicCluster(zigbeeDevice.get(), ENDPOINT_ID, NWK_ADDRESS));
            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, ClusterID(BASIC_CLUSTER))).WillOnce(Return(cluster));

            string objectName = "Z" + ZCL_uint16_Attribute::name();

            js << objectName << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << BASIC_CLUSTER << "," << APPLICATION_VERSION_ID << ");";

            jsExecuter->run(js.str());
            sleep(1);
            jsExecuter->join();

            jsExecuter.reset();
        }

        TEST_F(JavaScriptExecuterTest, creating_invalid_attribute_ZCL_uint16_and_then_valid) {
            ZEndpoint zEndpoint{NWK_ADDRESS, ENDPOINT_ID, PROFILE_ID, DEVICE_ID, DEVICE_VER, IN_CLUSTERS, OUT_CLUSTERS};
            ZDevice zDevice{extAddress, NWK_ADDRESS, 0, {zEndpoint}};
            std::stringstream jsException;
            std::stringstream jsRight;
            jsExecuter = make_unique<JavaScriptExecuter>(singletonObjects, std::chrono::seconds(10));
            EXPECT_CALL(*zDevices, exists(extAddress)).WillRepeatedly(Return(true));
            EXPECT_CALL(*zDevices, getDevice(extAddress)).WillRepeatedly(Return(&zDevice));
            std::shared_ptr<Cluster> cluster(new BasicCluster(zigbeeDevice.get(), ENDPOINT_ID, NWK_ADDRESS));
            EXPECT_CALL(clustersMock, getCluster(NWK_ADDRESS, ENDPOINT_ID, ClusterID(BASIC_CLUSTER))).WillRepeatedly(Return(cluster));

            string objectName_16uint = "Z" + ZCL_uint16_Attribute::name();
            string objectName_8uint = "Z" + ZCL_uint8_Attribute::name();

            jsException << objectName_16uint << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << BASIC_CLUSTER << "," << APPLICATION_VERSION_ID << ");";

            jsExecuter->run(jsException.str());
            sleep(1);
            jsExecuter->join();


            jsRight << objectName_8uint << "('" << EXTENDED_ADDRESS << "', " << (int)ENDPOINT_ID.getId() << ", " << BASIC_CLUSTER << "," << APPLICATION_VERSION_ID << ");";
            jsExecuter->run(jsRight.str());
            jsExecuter->join();


            jsExecuter.reset();
        }

    } /* namespace test */
} /* namespace zigbee */
