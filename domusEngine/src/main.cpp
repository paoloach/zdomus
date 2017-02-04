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

#include "JavaScript/JSManager.h"
#include "httpServer/DEHttpRequestHandlerFactory.h"
#include "httpServer/HttpServer.h"
#include "ZigbeeData/RequestDevices.h"

using namespace zigbee;
using namespace boost::program_options;

extern unsigned char natives_blob_bin[];
extern unsigned int natives_blob_bin_len;
extern unsigned char snapshot_blob_bin[];
extern unsigned int snapshot_blob_bin_len;

static constexpr auto CONFIGURATION_OPTION = "configuration";
static constexpr auto HELP = "help";
static constexpr auto DEFAULT_CONFIG_FILE = "/home/paolo/workspace_luna/domus_engine_copy/configuration/domusEngine.xml";
static constexpr auto LOGGIN_SETTINGS="logging";
static constexpr auto ZDRIVER="zdriver";


variables_map getVariableMap(size_t argc, char const *argv[]);

using namespace v8;

void initV8(int , const char *argv[]) {
    V8::InitializeICUDefaultLocation(argv[0]);
 //   V8::InitializeExternalStartupData(argv[0]);


    StartupData nativeBlob;
    nativeBlob.data = (char *) natives_blob_bin;
    nativeBlob.raw_size = natives_blob_bin_len;
    V8::SetNativesDataBlob(&nativeBlob);

    StartupData snapshotBlob;
    snapshotBlob.data = (char *) snapshot_blob_bin;
    snapshotBlob.raw_size = snapshot_blob_bin_len;
    V8::SetSnapshotDataBlob(&snapshotBlob);


    Platform* platform = platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();
}

void exitV8() {
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
}

int main(int argc, const char *argv[]) {

    initV8(argc, argv);
    std::string configurationFileName = DEFAULT_CONFIG_FILE;

    ClusterTypeFactory clusterTypeFactory;
    variables_map vm = getVariableMap(argc, argv);

    if (vm.count("configuration")) {
        configurationFileName = vm[CONFIGURATION_OPTION].as<std::string>();
    }
    SingletonObjects singletons(std::move(configurationFileName), vm[ZDRIVER].as<std::string>());
    auto zDevices = singletons.getZDevices();

    TopologyCreation topologyCreation(singletons);
    RequestDevices requestDevices(singletons);

    zDevices->addObserver([&requestDevices](ZDevice * zDevice){requestDevices.request(zDevice);});

    topologyCreation.create();

    auto server = new http::HttpServer(singletons);

    while (true);


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
            (ZDRIVER, value<std::string>(), "driver for zigbee device (usb, serial, demo)");


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
