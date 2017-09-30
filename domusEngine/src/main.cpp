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
#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>
#include <v8.h>
#include <v8-platform.h>
#include <libplatform/libplatform.h>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>

#include "httpServer/RestHandler.h"
#include "JavaScript/JSManager.h"
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
static constexpr auto LOGGIN_SETTINGS = "logging";
static constexpr auto ZDRIVER = "zdriver";


variables_map getVariableMap(size_t argc, char const *argv[]);

using namespace v8;

void initV8(int, const char *argv[]) {
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


    Platform *platform = platform::CreateDefaultPlatform();
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

    variables_map vm = getVariableMap(argc, argv);

    if (vm.count("configuration")) {
        configurationFileName = vm[CONFIGURATION_OPTION].as<std::string>();
    }
    SingletonObjects singletons(std::move(configurationFileName), vm[ZDRIVER].as<std::string>());
    auto zDevices = singletons.getZDevices();

    TopologyCreation topologyCreation(singletons);
    RequestDevices requestDevices(singletons);

    zDevices->addObserver([&requestDevices](ZDevice *zDevice) { requestDevices.request(zDevice); });

    topologyCreation.create();

    zigbee::http::RestHandler restHandler{singletons};

    restHandler.start();

    exitV8();
}

variables_map getVariableMap(size_t argc, char const *argv[]) {
    options_description desc("Allowed options");
    boost::log::trivial::severity_level logSeverity;
    desc.add_options()(HELP, "help")(CONFIGURATION_OPTION, value<std::string>(), "configuration file")(LOGGIN_SETTINGS, value<boost::log::trivial::severity_level>(&logSeverity),
                                                                                                       "Logging settings")(ZDRIVER, value<std::string>(),
                                                                                                                           "driver for zigbee device (usb, serial, demo)");


    variables_map vm{};
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    boost::log::add_common_attributes();
    boost::log::core::get()->add_global_attribute("Scope", boost::log::attributes::named_scope());
    boost::log::core::get()->set_filter( boost::log::trivial::severity >= boost::log::trivial::trace );

    auto fmtTimeStamp = boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
    auto fmtThreadId = boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID");
    auto fmtSeverity = boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity");
    auto fmtScope = boost::log::expressions::format_named_scope("Scope",
                                                                boost::log::keywords::format = "%n",
                                                                boost::log::keywords::iteration = boost::log::expressions::reverse,
                                                                boost::log::keywords::depth = 2);
 //   boost::log::core::get()->set_filter(boost::log::trivial::severity >= logSeverity);

    boost::log::formatter logFmt =
            boost::log::expressions::format("[%1%] (%2%) [%3%] [%4%] %5%")
            % fmtTimeStamp % fmtThreadId % fmtSeverity % fmtScope
            % boost::log::expressions::smessage;
    auto consoleSink = boost::log::add_console_log(std::clog);
    consoleSink->set_formatter(logFmt);

    auto fsSink = boost::log::add_file_log(
            boost::log::keywords::file_name = "domusEngine_%Y-%m-%d_%H-%M-%S.%N.log",
            boost::log::keywords::rotation_size = 10 * 1024 * 1024,
            boost::log::keywords::min_free_space = 300 * 1024 * 1024,
            boost::log::keywords::open_mode = std::ios_base::app);
    fsSink->set_formatter(logFmt);
    fsSink->locked_backend()->auto_flush(true);

    BOOST_LOG_TRIVIAL(info) << "Info Log in Test()";

    std::cout << "Log set" << std::endl;

    BOOST_LOG_TRIVIAL(info) << "severity " << logSeverity;

    if (vm.count(HELP)) {
        std::cout << desc << std::endl;
        exit(1);
    }
    return vm;
}
