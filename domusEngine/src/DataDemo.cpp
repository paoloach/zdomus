//
// Created by paolo on 07/10/16.
//

#include <zigbee/messageStructure/AnnunceMessage.h>
#include "Utils/SingletonObjectsImpl.h"
#include "ZigbeeData/ZDevices.h"
using namespace zigbee;

void add1Demo(SingletonObjects  & singletons){

    auto zDevices = singletons.getZDevices();

    AnnunceMessage annunceMsg;
    annunceMsg.nwkAddr = 1234;
    annunceMsg.extAddr[0] = 1;
    annunceMsg.extAddr[1] = 2;
    annunceMsg.extAddr[2] = 3;
    annunceMsg.extAddr[3] = 4;
    annunceMsg.extAddr[4] = 5;
    annunceMsg.extAddr[5] = 6;
    annunceMsg.extAddr[6] = 7;
    annunceMsg.extAddr[7] = 8;
    zDevices->put(annunceMsg);


    AnnunceMessage annunceMsg2;
    annunceMsg2.nwkAddr = 1235;
    annunceMsg2.extAddr[0] = 9;
    annunceMsg2.extAddr[1] = 10;
    annunceMsg2.extAddr[2] = 11;
    annunceMsg2.extAddr[3] = 12;
    annunceMsg2.extAddr[4] = 13;
    annunceMsg2.extAddr[5] = 14;
    annunceMsg2.extAddr[6] = 15;
    annunceMsg2.extAddr[7] = 16;
    zDevices->put(annunceMsg2);


    annunceMsg2.nwkAddr = 1232;
    annunceMsg2.extAddr[0] = 9;
    annunceMsg2.extAddr[1] = 20;
    annunceMsg2.extAddr[2] = 21;
    annunceMsg2.extAddr[3] = 22;
    annunceMsg2.extAddr[4] = 23;
    annunceMsg2.extAddr[5] = 24;
    annunceMsg2.extAddr[6] = 25;
    annunceMsg2.extAddr[7] = 26;
    zDevices->put(annunceMsg2);

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1234;
        simpleDescMessage.endpoint = 2;
        simpleDescMessage.numInClusters = 3;
        simpleDescMessage.numOutClusters = 0;
        simpleDescMessage.appDeviceId = 0x51; // SMART PLUG
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::METERING;
        simpleDescMessage.clustersList[3] = ClustersId::ON_OFF_CLUSTER;
        zDevices->put(simpleDescMessage);
    }

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1234;
        simpleDescMessage.endpoint = 4;
        simpleDescMessage.numInClusters = 2;
        simpleDescMessage.numOutClusters = 4;
        simpleDescMessage.appDeviceId = 0; // ON OFF SWITCH
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
        simpleDescMessage.clustersList[3] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[4] = ClustersId::SCENE_CLUSTER;
        simpleDescMessage.clustersList[5] = ClustersId::GROUPS_CLUSTER;
        zDevices->put(simpleDescMessage);
    }

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1234;
        simpleDescMessage.endpoint = 6;
        simpleDescMessage.numInClusters = 2;
        simpleDescMessage.numOutClusters = 4;
        simpleDescMessage.appDeviceId = 0x103; // ON OFF LIGHT SWITCH
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
        simpleDescMessage.clustersList[3] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[4] = ClustersId::SCENE_CLUSTER;
        simpleDescMessage.clustersList[5] = ClustersId::GROUPS_CLUSTER;
        zDevices->put(simpleDescMessage);
    }

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1235;
        simpleDescMessage.endpoint = 5;
        simpleDescMessage.numInClusters = 3;
        simpleDescMessage.numOutClusters = 0;
        simpleDescMessage.appDeviceId = 0x302; // Temp sensor
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::TEMPERATURE_MEASUREMENT;
        zDevices->put(simpleDescMessage);
    }

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1235;
        simpleDescMessage.endpoint = 7;
        simpleDescMessage.numInClusters = 5;
        simpleDescMessage.numOutClusters = 0;
        simpleDescMessage.appDeviceId = 0x02; // On off output
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
        simpleDescMessage.clustersList[3] = ClustersId::SCENE_CLUSTER;
        simpleDescMessage.clustersList[4] = ClustersId::GROUPS_CLUSTER;
        zDevices->put(simpleDescMessage);
    }

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1235;
        simpleDescMessage.endpoint = 11;
        simpleDescMessage.numInClusters = 5;
        simpleDescMessage.numOutClusters = 0;
        simpleDescMessage.appDeviceId = 0x100; // On off light
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::ON_OFF_CLUSTER;
        simpleDescMessage.clustersList[3] = ClustersId::SCENE_CLUSTER;
        simpleDescMessage.clustersList[4] = ClustersId::GROUPS_CLUSTER;
        zDevices->put(simpleDescMessage);
    }

    {
        SimpleDescMessage simpleDescMessage;
        simpleDescMessage.nwkAddr = 1232;
        simpleDescMessage.endpoint = 7;
        simpleDescMessage.numInClusters = 3;
        simpleDescMessage.numOutClusters = 0;
        simpleDescMessage.appDeviceId = 0x302; // Temp sensor
        simpleDescMessage.clustersList[0] = ClustersId::BASIC_CLUSTER;
        simpleDescMessage.clustersList[1] = ClustersId::IDENTIFY_CLUSTER;
        simpleDescMessage.clustersList[2] = ClustersId::TEMPERATURE_MEASUREMENT;
        zDevices->put(simpleDescMessage);
    }
    singletons.getBindTable().add(BindResponse(NwkAddr(1234), EndpointID(4),ClusterID(ClustersId::ON_OFF_CLUSTER), NwkAddr(1235), EndpointID(11)));
    singletons.getBindTable().add(BindResponse(NwkAddr(1234), EndpointID(4),ClusterID(ClustersId::ON_OFF_CLUSTER), NwkAddr(1235), EndpointID(7)));
}
