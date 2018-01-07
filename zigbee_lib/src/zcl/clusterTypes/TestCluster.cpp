//
// Created by Paolo Achdjian on 02/13/16.
// Copyright (c) Paolo Achdjian All rights reserved.

//
#include "src/zcl/attributeTypes/implementation/ZCLuint8AttributeImpl.h"
#include "TestCluster.h"

namespace zigbee {
    static std::vector<ClusterImpl::AttributeDef> attributesDef{
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 0, "test0", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 1, "test1", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 2, "test2", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 3, "test3", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 4, "test4", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 5, "test5", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 6, "test6", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 7, "test7", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 8, "test8", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 9, "test9", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 10, "test10", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 11, "test11", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 12, "test12", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 13, "test13", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 14, "test14", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 15, "test15", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 16, "test16", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 17, "test17", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 18, "test18", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 19, "test19", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 20, "test20", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 21, "test21", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 22, "test22", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 23, "test23", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 24, "test24", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 25, "test25", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 26, "test26", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 27, "test27", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 28, "test28", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 29, "test29", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 30, "test30", true),
            ClusterImpl::AttributeDef(ZCLTypeDataType::ZCLTypeUInt32, 31, "test31", true)
    };

    TestCluster::TestCluster(ZigbeeDevice * zigbeeDevice, const EndpointID endpoint, NwkAddr networkAddress) :
            ClusterImpl(zigbeeDevice, endpoint, networkAddress) {
        createAttributes(attributesDef);

    }

    ClusterID TestCluster::getId() const {
        return Test;
    }

    std::string TestCluster::getClusterName() const {
        return "Test ClusterImpl";
    }

}
