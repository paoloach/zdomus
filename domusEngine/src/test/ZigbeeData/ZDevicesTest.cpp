/*
 * ZDevicesTest.cpp
 *
 *  Created on: 29/nov/2014
 *      Author: Paolo Achdjian
 */

#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include "../../ZigbeeData/ExtAddress.h"
#include "ZDevicesTest.h"
#include "jsonFields.h"

using boost::property_tree::ptree;
using boost::property_tree::json_parser::write_json;
using namespace ::testing;
using std::cout;
using std::endl;

namespace zigbee {


    ZDevicesTest::~ZDevicesTest() {
    }

    static GenericMessage annunceMsg1{1};
    static GenericMessage simpleeMsg{2};
    static AnnunceMessage annunce1{annunceMsg1, 2, {3, 4, 5, 6, 7, 8, 9, 10}, 11};
    static AnnunceMessage annunce2{annunceMsg1, 102, {11, 12, 13, 14, 15, 16, 17, 18}, 111};
    static SimpleDescMessage simpleDesc1{simpleeMsg, 2 /*nwkAddr*/, 101/*endpoint*/, 102 /*appProfId*/, 103 /*appDeviceId*/, 104 /* appDevVer*/, 1 /*numInClusters*/,
                                         1 /*numOutClusters*/, 2, 3};

    void ZDevicesTest::SetUp() {
        std::stringstream stream;
        std::stringstream stream2;
        zDevices = new ZDevices{};
        ExtAddress extAddress(annunce1.extAddr);
        stream << extAddress;
        extAddr1 = stream.str();

        ExtAddress extAddress2(annunce2.extAddr);
        stream2 << extAddress2;
        extAddr2 = stream2.str();
    }

    void ZDevicesTest::TearDown() {
        delete zDevices;
    }

    TEST_F(ZDevicesTest, at_begin_return_empty) {
        ptree properties = zDevices->getDifferences(0);
        ASSERT_THAT(properties.size(), Eq(0));
    }

    TEST_F(ZDevicesTest, with_a_device) {

        zDevices->put(annunce1);
        ptree properties = zDevices->getDifferences(0);
        ASSERT_THAT(properties.size(), Eq(2));
        ASSERT_THAT(properties.get<int>(TOKEN_NAME), Eq(1));
        ptree zDevice = properties.get_child(DEVICE);
        ASSERT_THAT(zDevice.empty(), Eq(false));

        ASSERT_THAT(zDevice.get<int>(SHORT_ADDR_NAME), Eq(annunce1.nwkAddr));
        ASSERT_THAT(zDevice.get<int>(CAPABILITY_NAME), Eq(annunce1.capabilities));
        ASSERT_THAT(zDevice.get<std::string>(EXT_ADDR_NAME), Eq(extAddr1));
    }


    TEST_F(ZDevicesTest, annunce_and_simpleDesc) {
        zDevices->put(annunce1);
        ptree properties = zDevices->getDifferences(0);
        zDevices->put(simpleDesc1);
        properties = zDevices->getDifferences(1);
        ASSERT_THAT(properties.get<int>(TOKEN_NAME), Eq(2));
        ptree zDevice = properties.get_child(DEVICE);

    }


} /* namespace zigbee */
