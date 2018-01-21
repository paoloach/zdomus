//
// Created by paolo on 25/04/17.
//

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/fiber/fiber.hpp>
#include <boost/fiber/operations.hpp>
#include "../Utils/LogConstants.h"
#include "RestActions/ShowHello.h"
#include "RestActions/ShowWhoAreYou.h"
#include "RestHandlerImpl.h"
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
#include "RestActions/ShowPowerNode.h"
#include "RestActions/GetChildren.h"
#include "RestActions/DeleteDevice.h"


using namespace Pistache::Rest::Routes;
using namespace std::chrono_literals;

namespace zigbee::http {
    static Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(8080));

    RestHandlerImpl::RestHandlerImpl(zigbee::SingletonObjects *singletons) {
        getPath("/hello", ShowHello{});
        getPath("/who_are_you", ShowWhoAreYou{});
        getPath("/devices", ShowDevices{singletons});
        getPath("/devices/topology", ShowTopology{singletons});
        getPath("/devices/:device", ShowDevice{singletons});
        getPath("/devices/:device/power", ShowPowerNode{singletons});
        getPath("/devices/:device/children", GetChildren{singletons});
        getPath("/devices/:device/info", ShowDeviceInfo{singletons});
        getPath("/devices/:device/endpoint/:endpoint", ShowEndpoint{singletons});
        getPath("/devices/:device/endpoint/:endpoint/cluster/in/:cluster", ShowInCluster{singletons});
        getPath("/devices/:device/endpoint/:endpoint/cluster/out/:cluster", ShowOutCluster{singletons});
        getPath("/devices/:device/endpoint/:endpoint/cluster/in/:cluster/attributes", ShowAttributeFactory{singletons});
        getPath("/binds", ShowBindTable{singletons});

        Post(router, "/devices/:device/endpoint/:endpoint/cluster/in/:cluster/command/:command", ExecuteCmd{singletons});
        Post(router, "/devices/:device/endpoint/:endpoint/cluster/in/:cluster/attributes", UpdateAttributes{singletons});
        Post(router, "/reset", ExecuteReset{singletons});
        Post(router, "/bind/src/:srcDevice/endpoint/:srcEndpoint/cluster/:cluster/dst/:dstDevice/endpoint/:dstEndpoint", ExecuteBind{singletons, true});

        Delete(router, "/bind/src/:srcDevice/endpoint/:srcEndpoint/cluster/:cluster/dst/:dstDevice/endpoint/dstEndpoint", ExecuteBind{singletons, false});
        Delete(router, "/devices/:device/", DeleteDevice{singletons});

        commandFiber = boost::fibers::fiber([this]() { commandHandler(); });
    }

    void RestHandlerImpl::start() {
        channel.push(Cmd::Start);
    }

    void RestHandlerImpl::addGetPath(std::string &&path, Pistache::Rest::Route::Handler &&fn) {
        if (pathGetUsed.count(path) == 0) {
            BOOST_LOG_NAMED_SCOPE(REST);
            BOOST_LOG_TRIVIAL(info) << "Add GET path: " << path;
            getPath(std::move(path), std::move(fn));
            channel.push(Cmd::Shutdown);
            channel.push(Cmd::Start);
            pathGetUsed.insert(path);
        }
    }

    void RestHandlerImpl::commandHandler() {
        for (auto command: channel) {
            switch (command) {
                case Cmd::Start:
                    BOOST_LOG_TRIVIAL(info) << "Start http server";
                    server = new Pistache::Http::Endpoint(addr);
                    server->init(Pistache::Http::Endpoint::options().threads(1).flags(Pistache::Tcp::Options::ReuseAddr));
                    server->setHandler(router.handler());
                    server->serveThreaded();
                    break;
                case Cmd::Shutdown:
                    BOOST_LOG_TRIVIAL(info) << "Shutdown http server";
                    server->shutdown();
                    delete server;
                    break;
            }
        }
    }

    void RestHandlerImpl::getPath(std::string &&path, Pistache::Rest::Route::Handler &&fn) {
        router.get(path, fn);
        pathGetUsed.insert(path);
    }
}

