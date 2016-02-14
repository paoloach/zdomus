//
// Created by Paolo Achdjian on 02/13/16.
// Copyright (c) Paolo Achdjian All rights reserved.

//
#include "../attributeTypes/ZCLuint8Attribute.h"
#include "TestCluster.h"

namespace zigbee {
    static std::vector<Cluster::AttributeDef> attributesDef{
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 0, "test0", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 1, "test1", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 2, "test2", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 3, "test3", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 4, "test4", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 5, "test5", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 6, "test6", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 7, "test7", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 8, "test8", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 9, "test9", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 10, "test10", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 11, "test11", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 12, "test12", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 13, "test13", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 14, "test14", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 15, "test15", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 16, "test16", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 17, "test17", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 18, "test18", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 19, "test19", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 20, "test20", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 21, "test21", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 22, "test22", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 23, "test23", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 24, "test24", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 25, "test25", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 26, "test26", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 27, "test27", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 28, "test28", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 29, "test29", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 30, "test30", true),
            Cluster::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 31, "test31", true)
    };

    TestCluster::TestCluster(const std::shared_ptr<ZigbeeDevice> &zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
            Cluster(zigbeeDevice, endpoint, networkAddress) {
        createAttributes(attributesDef);

    }

    ClusterID TestCluster::getId() const {
        return Test;
    }

    std::string TestCluster::getClusterName() const {
        return "Test Cluster";
    }

}
