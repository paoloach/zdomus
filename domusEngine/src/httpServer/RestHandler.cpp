//
// Created by paolo on 25/04/17.
//

#include "RestActions/ShowHello.h"
#include "RestActions/ShowWhoAreYou.h"
#include "RestHandler.h"
#include "RestActions/ShowDevices.h"
#include "RestActions/ShowTopology.h"
#include "RestActions/ShowDevice.h"
#include "RestActions/ShowDeviceInfo.h"
#include "RestActions/ShowEndpoint.h"
#include "RestActions/ShowInCluster.h"
#include "RestActions/ShowOutCluster.h"
#include "RestActions/ShowAttributeFactory.h"
#include "RestActions/UpdateAttributes.h"
#include "RestActions/ExecuteCmd.h"
#include "RestActions/ShowBindTable.h"
#include "RestActions/ExecuteReset.h"
#include "RestActions/ExecuteBind.h"


using namespace Net::Rest::Routes;
using namespace zigbee::http;

namespace zigbee {
    namespace http {
        static Net::Address addr(Net::Ipv4::any(), Net::Port(8080));

        RestHandler::RestHandler(zigbee::SingletonObjects &singletons) : server(addr) {
            Get(router, "/hello", ShowHello{});
            Get(router, "/who_are_you", ShowWhoAreYou{});
            Get(router, "/devices", ShowDevices{singletons});
            Get(router, "/devices/topology", ShowTopology{singletons});
            Get(router, "/devices/:device", ShowDevice{singletons});
            Get(router, "/devices/:device/info", ShowDeviceInfo{singletons});
            Get(router, "/devices/:device/endpoint/:endpoint", ShowEndpoint{singletons});
            Get(router, "/devices/:device/endpoint/:endpoint/cluster/in/:cluster", ShowInCluster{singletons});
            Get(router, "/devices/:device/endpoint/:endpoint/cluster/out/:cluster", ShowOutCluster{singletons});
            Get(router, "/devices/:device/endpoint/:endpoint/cluster/in/:cluster/attributes", ShowAttributeFactory{singletons});
            Get(router, "/binds", ShowBindTable{singletons});

            Post(router, "/devices/:device/endpoint/:endpoint/cluster/in/:cluster/command/:command", ExecuteCmd{singletons});
            Post(router, "/devices/:device/endpoint/:endpoint/cluster/in/:cluster/attributes", UpdateAttributes{singletons});
            Post(router, "/reset", ExecuteReset{singletons});
            Post(router, "/bind/src/:srcDevice/endpoint/:srcEndpoint/cluster/:cluster/dst/:dstDevice/endpoint/:dstEndpoint", ExecuteBind{singletons, true});

            Delete(router, "/bind/src/:srcDevice/endpoint/:srcEndpoint/cluster/:cluster/dst/:dstDevice/endpoint/dstEndpoint", ExecuteBind{singletons, false});


            auto opts = Net::Http::Endpoint::options().threads(1);
            server.init(opts);
            server.setHandler(router.handler());

        }

        void RestHandler::start() {
            server.serve();
        }

        void RestHandler::addGetPath(std::string path, Net::Rest::Route::Handler fn) {
            Get(router, std::move(path), std::move(fn));
        }
    }
}

