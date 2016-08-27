/*
 * main.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include <boost/asio/impl/io_service.ipp>
#include <boost/asio/deadline_timer_service.hpp>

#include <zigbee/messageStructure/AnnunceMessage.h>
#include <zcl/Cluster.h>
#include <zcl/ClustersEnum.h>
#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>
#include <v8.h>
#include <v8-platform.h>
#include <libplatform/libplatform.h>
#include <boost/log/core/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "IO/Server.h"

#include "JavaScript/JSManager.h"
#include "httpServer/DEHttpRequestHandlerFactory.h"
#include "httpServer/HttpServer.h"

using namespace zigbee;
using namespace boost::program_options;

extern unsigned char natives_blob_bin[];
extern unsigned int natives_blob_bin_len;
extern unsigned char snapshot_blob_bin[];
extern unsigned int snapshot_blob_bin_len;

static constexpr auto CONFIGURATION_OPTION = "configuration";
static constexpr auto DEMO_DATA = "demo";
static constexpr auto HELP = "help";
static constexpr auto DEFAULT_CONFIG_FILE = "/home/paolo/workspace_luna/domus_engine_copy/configuration/domusEngine.xml";
static constexpr auto LOGGIN_SETTINGS="logging";


variables_map getVariableMap(size_t argc, char const *argv[]);

void add1Demo(SingletonObjects  & singletons){

    std::shared_ptr<ZDevices> zDevices = singletons.getZDevices();

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
    singletons.getBindTable().add(BindResponse(NwkAddr(1234), EndpointID(4),ClusterID(ClustersId::ON_OFF_CLUSTER), NwkAddr(1235), EndpointID(11)));
    singletons.getBindTable().add(BindResponse(NwkAddr(1234), EndpointID(4),ClusterID(ClustersId::ON_OFF_CLUSTER), NwkAddr(1235), EndpointID(7)));
}



using namespace v8;

void initV8() {
    V8::InitializeICU();


    StartupData nativeBlob;
    nativeBlob.data = (char *)natives_blob_bin;
    nativeBlob.raw_size = natives_blob_bin_len;
    V8::SetNativesDataBlob(&nativeBlob);

    StartupData snapshotBlob;
    snapshotBlob.data = (char *)snapshot_blob_bin;
    snapshotBlob.raw_size = snapshot_blob_bin_len;
    V8::SetSnapshotDataBlob(&snapshotBlob);

    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

}

void enableDemo(const variables_map &vm, SingletonObjects  & singletons){
    if (vm.count(DEMO_DATA)) {
        add1Demo(singletons);
    }
}

void exitV8() {
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
}

int main(int argc, const char *argv[]) {

    initV8();
    std::string configurationFileName = DEFAULT_CONFIG_FILE;

    ClusterTypeFactory clusterTypeFactory;
    variables_map vm = getVariableMap(argc, argv);

    if (vm.count("configuration")) {
        configurationFileName = vm[CONFIGURATION_OPTION].as<std::string>();
    }
    SingletonObjects singletons(std::move(configurationFileName),vm.count(DEMO_DATA));

    enableDemo(vm, singletons);

    auto server = new http::HttpServer(singletons);

    std::remove(Server::socketPath.c_str());

    //zigbee::Server s(singletons.getIO(), singletons.getZDevices(), singletons.getZigbeeDevice(),singletons.getAttributeDataContainer());
    singletons.getIO().run();


    exitV8();
    delete server;
}

variables_map getVariableMap(size_t argc, char const *argv[]) {
    options_description desc("Allowed options");
    boost::log::trivial::severity_level logSeverity;
    desc.add_options()
            (HELP, "help")
            (CONFIGURATION_OPTION, value<std::string>(), "configuration file")
            (LOGGIN_SETTINGS, value<boost::log::trivial::severity_level>(&logSeverity), "Logging settings")
            (DEMO_DATA, "enable demo data");


    variables_map vm{};
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    boost::log::core::get()->set_filter(boost::log::trivial::severity >= logSeverity);
    BOOST_LOG_TRIVIAL(info) << "severity " << logSeverity;

    if (vm.count(HELP)) {
        std::cout << desc << std::endl;
        exit(1);
    }
    return vm;
}
