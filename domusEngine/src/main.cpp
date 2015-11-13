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

#include "IO/Server.h"

#include "JavaScript/JSManager.h"
#include "httpServer/DEHttpRequestHandlerFactory.h"
#include "httpServer/HttpServer.h"

using namespace zigbee;
using namespace boost::program_options;

static constexpr auto CONFIGURATION_OPTION="configuration";
static constexpr auto DEMO_DATA="demo";
static constexpr auto HELP="help";
static constexpr auto DEFAULT_CONFIG_FILE = "/home/paolo/workspace_luna/domus_engine_copy/configuration/domusEngine.xml";

variables_map getVariableMap(size_t argc, char const *argv[]);

void add1Demo(std::shared_ptr<ZDevices> zDevices, const boost::system::error_code& ) {
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
}

void initV8() {
	v8::V8::InitializeICU();
	std::unique_ptr<v8::Platform> platform(v8::platform::CreateDefaultPlatform());
	v8::V8::InitializePlatform(platform.get());
	v8::V8::Initialize();
}

void enableDemo(const variables_map& vm, boost::asio::io_service& io, const std::shared_ptr<ZDevices> & zDevices) {
	if (vm.count(DEMO_DATA)) {
		boost::asio::deadline_timer timer1(io, boost::posix_time::seconds(5));

		timer1.async_wait(boost::bind(&add1Demo, zDevices, boost::asio::placeholders::error));
	}
}

void exitV8() {
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}

int main(int argc, const char * argv[]){

	initV8();
	std::string configurationFileName = DEFAULT_CONFIG_FILE;


	ClusterTypeFactory clusterTypeFactory;
	variables_map vm = getVariableMap(argc, argv);


	if (vm.count("configuration")){
		configurationFileName = vm[CONFIGURATION_OPTION].as<std::string>();
	}

	SingletonObjects singletons(std::move(configurationFileName));


	enableDemo(vm, singletons.getIO(), singletons.getZDevices());


	auto server = new http::HttpServer(singletons);

	std::remove(Server::socketPath.c_str());

	//zigbee::Server s(singletons.getIO(), singletons.getZDevices(), singletons.getZigbeeDevice(),singletons.getAttributeDataContainer());
	singletons.getIO().run();


	exitV8();
	delete server;
}

variables_map getVariableMap(size_t argc, char const *argv[]) {
	options_description desc("Allowed options");
	desc.add_options()
			(HELP, "help")
			(CONFIGURATION_OPTION, value<std::string>(),"configuration file")
			(DEMO_DATA, "enable demo data");


	variables_map vm {};
	store(parse_command_line(argc,argv,desc),vm);
	notify(vm);

	if (vm.count(HELP)) {
	    std::cout << desc << std::endl;
	    exit(1);
	}
	return vm;
}
