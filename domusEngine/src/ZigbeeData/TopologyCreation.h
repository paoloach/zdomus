//
// Created by paolo on 26/09/16.
//

#ifndef DOMUS_ENGINE_TOPOLOGY_CREATION_H
#define DOMUS_ENGINE_TOPOLOGY_CREATION_H

#include <boost/fiber/mutex.hpp>
#include <boost/fiber/unbuffered_channel.hpp>
#include <boost/fiber/fiber.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include "TopologyParent.h"

namespace zigbee {
    class ZDevice;
    class TopologyParent;
    class SingletonObjects;

    class TopologyCreation {
    private:
        SingletonObjects*singletonObjects;
        boost::fibers::fiber topologyFiber;
        bool stop;
    public:
        std::map<ExtAddress, std::unique_ptr<TopologyParent> > devices;
        boost::fibers::unbuffered_channel<TopologyParent *>  channel;

    public:
        TopologyCreation(SingletonObjects *singletonObjects) : singletonObjects(singletonObjects) {}

        ~TopologyCreation();

        void start();

    private:
        void manageRequest();

    };
}


#endif //DOMUS_ENGINE_TOPOLOGY_CREATION_H
