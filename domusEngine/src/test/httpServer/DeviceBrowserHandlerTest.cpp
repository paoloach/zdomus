/*
 * DeviceBrowserHandlerTest.cpp
 *
 *  Created on: 14/apr/2015
 *      Author: Paolo Achdjian
 */
#include <typeinfo>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/MediaType.h>
#include <iomanip>
#include <boost/filesystem/path.hpp>

#include <sstream>
#include "DeviceBrowserHandlerTest.h"
#include "../../ZigbeeData/Exceptions/InvalidZDevice.h"
#include "../../httpServer/DeviceBrowserHandler.h"
#include "../Mocks/http/HTTPServerRequestMock.h"

#include "../Mocks/ClusterMock.h"
#include "../Mocks/ZCLAttributeMock.h"
#include "ZDeviceFixture.h"

namespace zigbee {
    namespace http {
        namespace test {

            using boost::filesystem::path;
            using namespace testing;

            static const Poco::Net::MediaType MEDIA_TYPE_JSON("application", "json");

            constexpr int DeviceBrowserHandlerTest::attributeId;
            static std::string attributeValue("value");

            DeviceBrowserHandlerTest::DeviceBrowserHandlerTest() {
                attributeStatus = ZCLAttribute::Available;
                attributeAvailable = true;
                clusterInId = ZDeviceFixture::endpoint2_1.getInCluster()[0];
                clusterOutId = ZDeviceFixture::endpoint2_1.getOutCluster()[0];
                endpoint = ZDeviceFixture::endpoint2_1;
            }

            void DeviceBrowserHandlerTest::SetUp() {
                zDevicesMock = std::make_unique<zigbee::test::ZDevicesMock>();
                zigbeeDevice = std::make_unique<zigbee::test::ZigbeeDeviceMock>();
                clusterMock = std::make_shared<zigbee::test::ClusterMock>();
                attributeMock = std::make_shared<zigbee::test::ZCLAttributeMock>(nullptr, nullptr, 0,
                                                                                 ZCLTypeDataType::ZCLTypeInvalid,
                                                                                 "mock", false);
                EXPECT_CALL(response, send()).Times(AtMost(1)).WillOnce(ReturnRef(outStream));
                request.setMethod("GET");
                attributeAvailable = true;
                attributeStatus = ZCLAttribute::Available;
                EXPECT_CALL(singletonObjects, getZDevices()).Times(AnyNumber()).WillOnce(
                        Return(zDevicesMock.get()));
                EXPECT_CALL(singletonObjects, getZigbeeDevice()).Times(AnyNumber()).WillOnce(Return(zigbeeDevice.get()));
                EXPECT_CALL(singletonObjects, getClusters()).Times(AnyNumber()).WillOnce(Return(&clustersMock));
            }

            void DeviceBrowserHandlerTest::TearDown() {
                zDevicesMock.reset();
            }

            TEST_F(DeviceBrowserHandlerTest, allDevicesText) {
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI("/devices");
                std::vector<ZDevice *> devices = {&ZDeviceFixture::zDevice1, &ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevices()).WillOnce(Return(devices));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                ASSERT_THAT(resultString, Eq("1=10-11-12-13-14-15-16-17\n11=20-21-22-23-24-25-26-27\n"));
            }

            TEST_F(DeviceBrowserHandlerTest, allDevicesJSON) {
                std::stringstream expectedStream;
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI("/devices");

                request.setContentType(MEDIA_TYPE_JSON);
                std::vector<ZDevice *> devices = {&ZDeviceFixture::zDevice1, &ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevices()).WillOnce(Return(devices));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "{\"1\":\"" << ZDeviceFixture::zDevice1.getExtAddr() << "\",\"11\":\""
                               << ZDeviceFixture::zDevice2.getExtAddr() << "\"}\n";
                ASSERT_THAT(resultString, Eq(expectedStream.str()));
            }

            TEST_F(DeviceBrowserHandlerTest, oneDevicePlainText) {
                std::stringstream restPath;
                std::stringstream expectedStream;
                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr();
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                std::vector<ZDevice *> devices = {&ZDeviceFixture::zDevice1, &ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "extended_address=" << ZDeviceFixture::zDevice1.getExtAddr() << std::endl;
                expectedStream << "short_address=" << std::dec << ZDeviceFixture::zDevice1.getNwkAddr() << std::endl;
                expectedStream << "capability=" << (int) ZDeviceFixture::zDevice1.getCapabilities() << std::endl;
                expectedStream << "[endpoints]" << std::endl;
                int index = 0;
                for (auto endpoint : ZDeviceFixture::zDevice1.getEndpoints()) {
                    expectedStream << index << "=" << endpoint.first << std::endl;
                    index++;
                }
                ASSERT_THAT(resultString, expectedStream.str() );
            }

            TEST_F(DeviceBrowserHandlerTest, oneDeviceJSON) {
                std::stringstream restPath;
                std::stringstream expectedStream;
                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr();
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                request.setContentType(MEDIA_TYPE_JSON);
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();

                expectedStream << "{\"extended_address\":\"" << ZDeviceFixture::zDevice1.getExtAddr() << "\",";
                expectedStream << "\"short_address\":\"" << ZDeviceFixture::zDevice1.getNwkAddr() << "\",";
                expectedStream << "\"capability\":\"" << (int) ZDeviceFixture::zDevice1.getCapabilities() << "\",";
                expectedStream << "\"endpoints\":{\"0\":\"11\",\"1\":\"21\"}}\n";
                ASSERT_THAT(resultString, expectedStream.str());
            }

            TEST_F(DeviceBrowserHandlerTest, invalidDevice) {
                std::stringstream restPath;
                NwkAddr invalidDevice{123};

                restPath << "/devices/" << invalidDevice;
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(invalidDevice)).WillOnce(Throw(InvalidZDevice(invalidDevice)));

                deviceBrowserHandler->handleRequest(request, response);
                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            }

            TEST_F(DeviceBrowserHandlerTest, endpointPlainText) {
                std::stringstream restPath;
                std::stringstream expectedStream;

                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << endpoint.getEndpoint();
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "short_address=" << endpoint.getNwkAddr() << std::endl;
                expectedStream << "endpoint_id=" << endpoint.getEndpoint() << std::endl;
                expectedStream << "profile_id=" << (int) endpoint.getAppProfId() << std::endl;
                expectedStream << "device_id=" << (int) endpoint.getAppDeviceId() << std::endl;
                expectedStream << "device_version=" << (int) endpoint.getAppDevVer() << std::endl;
                expectedStream << "[input_clusters]" << std::endl;
                int index = 0;
                for (auto cluster : endpoint.getInCluster()) {
                    expectedStream << index << "=" << cluster << std::endl;
                    index++;
                }
                expectedStream << "[output_clusters]" << std::endl;
                index = 0;
                for (auto cluster : endpoint.getOutCluster()) {
                    expectedStream << index << "=" << cluster << std::endl;
                    index++;

                }
                ASSERT_THAT(resultString, expectedStream.str());
            }

            TEST_F(DeviceBrowserHandlerTest, endpointJSon) {
                std::stringstream restPath;
                std::stringstream expectedStream;

                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << endpoint.getEndpoint();
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                request.setContentType(MEDIA_TYPE_JSON);
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();

                expectedStream << "{\"short_address\":\"" << endpoint.getNwkAddr() << "\",";
                expectedStream << "\"endpoint_id\":\"" << endpoint.getEndpoint() << "\",";
                expectedStream << "\"profile_id\":\"" << (int) endpoint.getAppProfId() << "\",";
                expectedStream << "\"device_id\":\"" << (int) endpoint.getAppDeviceId() << "\",";
                expectedStream << "\"device_version\":\"" << (int) endpoint.getAppDevVer() << "\",";
                expectedStream << "\"input_clusters\":{\"0\":\"7\",\"1\":\"8\",\"2\":\"9\"},";
                expectedStream << "\"output_clusters\":{\"0\":\"10\",\"1\":\"11\",\"2\":\"12\"}}\n";
                ASSERT_THAT(resultString, expectedStream.str());
            }

            TEST_F(DeviceBrowserHandlerTest, clusterInPlainText) {
                std::stringstream restPath;
                std::stringstream expectedStream;

                auto clusterMock = std::make_shared<zigbee::test::ClusterMock>();

                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << endpoint.getEndpoint() << "/cluster/in/" << clusterInId;
                request.setURI(restPath.str());
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                HTTPServerRequestMock request("GET", restPath.str());
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));
                EXPECT_CALL(clustersMock, getCluster(ZDeviceFixture::zDevice1.getNwkAddr(), endpoint.getEndpoint(),
                                                     clusterInId)).WillOnce(Return(clusterMock));

                EXPECT_CALL(*clusterMock, getId()).WillOnce(Return(ZDeviceFixture::clusterId));
                EXPECT_CALL(*clusterMock, getClusterName()).WillOnce(Return(ZDeviceFixture::clusterName));
                EXPECT_CALL(*clusterMock, getAttributes()).WillOnce(Return(ZDeviceFixture::attributes));
                EXPECT_CALL(*clusterMock, getCommands()).WillOnce(Return(ZDeviceFixture::commands));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "cluster id=" << ZDeviceFixture::clusterId << std::endl;
                expectedStream << "cluster name=" << ZDeviceFixture::clusterName << std::endl;
                expectedStream << "[attributes]" << std::endl;
                expectedStream << ZDeviceFixture::attribute1.id << "=" << ZDeviceFixture::attribute1.name << std::endl;
                expectedStream << ZDeviceFixture::attribute2.id << "=" << ZDeviceFixture::attribute2.name << std::endl;
                expectedStream << ZDeviceFixture::attribute3.id << "=" << ZDeviceFixture::attribute3.name << std::endl;
                expectedStream << "[commands]" << std::endl;
                expectedStream << ZDeviceFixture::command1.cmdId << "=" << ZDeviceFixture::command1.name << std::endl;
                expectedStream << ZDeviceFixture::command2.cmdId << "=" << ZDeviceFixture::command2.name << std::endl;
                expectedStream << ZDeviceFixture::command3.cmdId << "=" << ZDeviceFixture::command3.name << std::endl;

                ASSERT_THAT(resultString, expectedStream.str());
            }

            TEST_F(DeviceBrowserHandlerTest, clusterInJSON) {
                std::stringstream restPath;
                std::stringstream expectedStream;

                auto clusterMock = std::make_shared<zigbee::test::ClusterMock>();

                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << endpoint.getEndpoint() << "/cluster/in/" << clusterInId;
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                request.setContentType(MEDIA_TYPE_JSON);
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));
                EXPECT_CALL(clustersMock, getCluster(ZDeviceFixture::zDevice1.getNwkAddr(), endpoint.getEndpoint(),
                                                     clusterInId)).WillOnce(Return(clusterMock));

                EXPECT_CALL(*clusterMock, getId()).WillOnce(Return(ZDeviceFixture::clusterId));
                EXPECT_CALL(*clusterMock, getClusterName()).WillOnce(Return(ZDeviceFixture::clusterName));
                EXPECT_CALL(*clusterMock, getAttributes()).WillOnce(Return(ZDeviceFixture::attributes));
                EXPECT_CALL(*clusterMock, getCommands()).WillOnce(Return(ZDeviceFixture::commands));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "{\"cluster id\":\"" << ZDeviceFixture::clusterId << "\",";
                expectedStream << "\"cluster name\":\"" << ZDeviceFixture::clusterName << "\",";
                expectedStream << "\"attributes\":{";
                expectedStream << "\"" << ZDeviceFixture::attribute1.id << "\":\"" << ZDeviceFixture::attribute1.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::attribute2.id << "\":\"" << ZDeviceFixture::attribute2.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::attribute3.id << "\":\"" << ZDeviceFixture::attribute3.name
                               << "\"},";
                expectedStream << "\"commands\":{";
                expectedStream << "\"" << ZDeviceFixture::command1.cmdId << "\":\"" << ZDeviceFixture::command1.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::command2.cmdId << "\":\"" << ZDeviceFixture::command2.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::command3.cmdId << "\":\"" << ZDeviceFixture::command3.name
                               << "\"}}\n";

                ASSERT_THAT(resultString, expectedStream.str());
            }

            TEST_F(DeviceBrowserHandlerTest, clusterOutPlainText) {
                std::stringstream restPath;
                std::stringstream expectedStream;

                auto clusterMock = std::make_shared<zigbee::test::ClusterMock>();

                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << endpoint.getEndpoint() << "/cluster/out/" << clusterOutId;
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));
                EXPECT_CALL(clustersMock, getCluster(ZDeviceFixture::zDevice1.getNwkAddr(), endpoint.getEndpoint(),
                                                     clusterOutId)).WillOnce(Return(clusterMock));

                EXPECT_CALL(*clusterMock, getId()).WillOnce(Return(ZDeviceFixture::clusterId));
                EXPECT_CALL(*clusterMock, getClusterName()).WillOnce(Return(ZDeviceFixture::clusterName));
                EXPECT_CALL(*clusterMock, getAttributes()).WillOnce(Return(ZDeviceFixture::attributes));
                EXPECT_CALL(*clusterMock, getCommands()).WillOnce(Return(ZDeviceFixture::commands));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "cluster id=" << ZDeviceFixture::clusterId << std::endl;
                expectedStream << "cluster name=" << ZDeviceFixture::clusterName << std::endl;
                expectedStream << "[attributes]" << std::endl;
                expectedStream << ZDeviceFixture::attribute1.id << "=" << ZDeviceFixture::attribute1.name << std::endl;
                expectedStream << ZDeviceFixture::attribute2.id << "=" << ZDeviceFixture::attribute2.name << std::endl;
                expectedStream << ZDeviceFixture::attribute3.id << "=" << ZDeviceFixture::attribute3.name << std::endl;
                expectedStream << "[commands]" << std::endl;
                expectedStream << ZDeviceFixture::command1.cmdId << "=" << ZDeviceFixture::command1.name << std::endl;
                expectedStream << ZDeviceFixture::command2.cmdId << "=" << ZDeviceFixture::command2.name << std::endl;
                expectedStream << ZDeviceFixture::command3.cmdId << "=" << ZDeviceFixture::command3.name << std::endl;

                ASSERT_THAT(resultString, expectedStream.str());
            }

            TEST_F(DeviceBrowserHandlerTest, clusterOutJSON) {
                std::stringstream restPath;
                std::stringstream expectedStream;

                auto clusterMock = std::make_shared<zigbee::test::ClusterMock>();

                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << endpoint.getEndpoint() << "/cluster/out/" << clusterOutId;
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                request.setURI(restPath.str());
                request.setContentType(MEDIA_TYPE_JSON);
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));
                EXPECT_CALL(clustersMock, getCluster(ZDeviceFixture::zDevice1.getNwkAddr(), endpoint.getEndpoint(),
                                                     clusterOutId)).WillOnce(Return(clusterMock));

                EXPECT_CALL(*clusterMock, getId()).WillOnce(Return(ZDeviceFixture::clusterId));
                EXPECT_CALL(*clusterMock, getClusterName()).WillOnce(Return(ZDeviceFixture::clusterName));
                EXPECT_CALL(*clusterMock, getAttributes()).WillOnce(Return(ZDeviceFixture::attributes));
                EXPECT_CALL(*clusterMock, getCommands()).WillOnce(Return(ZDeviceFixture::commands));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_OK);
                std::string resultString = outStream.str();
                expectedStream << "{\"cluster id\":\"" << ZDeviceFixture::clusterId << "\",";
                expectedStream << "\"cluster name\":\"" << ZDeviceFixture::clusterName << "\",";
                expectedStream << "\"attributes\":{";
                expectedStream << "\"" << ZDeviceFixture::attribute1.id << "\":\"" << ZDeviceFixture::attribute1.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::attribute2.id << "\":\"" << ZDeviceFixture::attribute2.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::attribute3.id << "\":\"" << ZDeviceFixture::attribute3.name
                               << "\"},";
                expectedStream << "\"commands\":{";
                expectedStream << "\"" << ZDeviceFixture::command1.cmdId << "\":\"" << ZDeviceFixture::command1.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::command2.cmdId << "\":\"" << ZDeviceFixture::command2.name
                               << "\",";
                expectedStream << "\"" << ZDeviceFixture::command3.cmdId << "\":\"" << ZDeviceFixture::command3.name
                               << "\"}}\n";

                ASSERT_THAT(resultString, expectedStream.str());
            }




            TEST_F(DeviceBrowserHandlerTest, executeCmdWithoutParams) {
                int cmd = 3;
                auto restPath = getRestForCmd(cmd);
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));

                HTTPServerRequestMock request("POST", restPath);
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));
                EXPECT_CALL(clustersMock, getCluster(ZDeviceFixture::zDevice1.getNwkAddr(), endpoint.getEndpoint(),
                                                     clusterInId)).WillOnce(Return(clusterMock));
                EXPECT_CALL(*clusterMock, getCmdParams(cmd)).WillOnce(
                        Return(std::vector<std::shared_ptr<ClusterCmdParamsBase>> {}));

                EXPECT_CALL(*clusterMock, executeComand(cmd, std::vector<uint8_t> {}));
                //EXPECT_CALL(*clusterMock,executeComand(_, _));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
            }

            TEST_F(DeviceBrowserHandlerTest, executeCmdParams) {
                uint32_t cmd = 3;
                std::unique_ptr<Poco::Net::HTTPRequestHandler> deviceBrowserHandler(
                        new DeviceBrowserHandler(singletonObjects));
                int param1{23};
                std::string param2{"param2"};
                auto cmdParam1 = std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeUInt16>>("param1");
                auto cmdParam2 = std::make_shared<ClusterCmdParams<ZCLTypeDataType::ZCLTypeStringChar>>("param2");
                Cluster::CommandDef comand{[](std::vector<uint8_t> &&) {}, cmd, "test comand",
                                           cmdParam1,
                                           cmdParam2
                };

                std::stringstream streamParams;
                streamParams << "?param1=" << param1 << "&param2=" << param2;
                auto restPath = getRestForCmd(cmd) + streamParams.str();
                HTTPServerRequestMock request("POST", restPath);
                std::vector<ZDevice> devices = {ZDeviceFixture::zDevice1, ZDeviceFixture::zDevice2};
                EXPECT_CALL(*zDevicesMock, getDevice(ZDeviceFixture::zDevice1.getNwkAddr())).WillOnce(
                        Return(&ZDeviceFixture::zDevice1));
                EXPECT_CALL(clustersMock, getCluster(ZDeviceFixture::zDevice1.getNwkAddr(), endpoint.getEndpoint(),
                                                     clusterInId)).WillOnce(Return(clusterMock));
                EXPECT_CALL(*clusterMock, getCmdParams(cmd)).WillOnce(
                        Return(std::vector<std::shared_ptr<ClusterCmdParamsBase>> {cmdParam1, cmdParam2}));

                std::vector<uint8_t> expectedVectorData{cmdParam1->getType().getRaw(param1)};
                auto param2Data = cmdParam2->getType().getRaw(param2);
                std::copy(param2Data.begin(), param2Data.end(), std::back_inserter(expectedVectorData));


                EXPECT_CALL(*clusterMock, executeComand(cmd, expectedVectorData));

                deviceBrowserHandler->handleRequest(request, response);

                ASSERT_THAT(response.getStatus(), Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
            }

            TEST_F(DeviceBrowserHandlerTest, listJavascriptFile) {

            }


            void DeviceBrowserHandlerTest::setExpectedCallForAttribute() {
                EXPECT_CALL(*clusterMock, getAttribute(ZDeviceFixture::attribute1.name)).Times(AtLeast(0)).WillOnce(
                        Return(attributeMock));
                EXPECT_CALL(*clusterMock, getAttribute(attributeId)).Times(AtLeast(0)).WillOnce(Return(attributeMock));
                EXPECT_CALL(*attributeMock, requestValue());
                EXPECT_CALL(*attributeMock, getIdentifier()).WillOnce(Return(attributeId));
                EXPECT_CALL(*attributeMock, getName()).WillOnce(Return(attributeName));
                EXPECT_CALL(*attributeMock, isReadOnly()).WillOnce(Return(attributeReadOnly));
                EXPECT_CALL(*attributeMock, getZCLType()).WillOnce(Return(attributeDataType));
                if (attributeAvailable) {
                    EXPECT_CALL(*attributeMock, isAvailable()).Times(AtLeast(4)).WillOnce(Return(false)).WillOnce(
                            Return(false)).WillOnce(Return(false)).WillRepeatedly(Return(true));
                } else {
                    EXPECT_CALL(*attributeMock, isAvailable()).Times(AtLeast(2)).WillRepeatedly(Return(true));
                }
                EXPECT_CALL(*attributeMock, isUnsupported()).Times(AtLeast(1)).WillOnce(Return(attributeUnsupported));
                EXPECT_CALL(*attributeMock, getStatus()).WillOnce(Return(attributeStatus));

                EXPECT_CALL(*attributeMock, getValue()).WillOnce(Return(attributeValue));
            }

            std::string DeviceBrowserHandlerTest::getRestForCmd(int cmd) {
                std::stringstream restPath;
                restPath << "/devices/" << ZDeviceFixture::zDevice1.getNwkAddr() << "/endpoint/"
                         << ZDeviceFixture::endpoint2_1.getEndpoint() << "/cluster/in/" << clusterInId << "/command/"
                         << cmd;
                return restPath.str();
            }

        } /* namespace test */
    } /* namespace http */
} /* namespace zigbee */
