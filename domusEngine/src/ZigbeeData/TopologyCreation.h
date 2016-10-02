//
// Created by paolo on 26/09/16.
//

#ifndef DOMUS_ENGINE_TOPOLOGY_CREATION_H
#define DOMUS_ENGINE_TOPOLOGY_CREATION_H


#include <set>
#include <thread>
#include <mutex>
#include <chrono>

namespace zigbee {
    class SingletonObjects;

    class ZDevice;

    class TopologyCreation {
    private:
        SingletonObjects &singletonObjects;
        std::set<NwkAddr> toDo;
        std::map<NwkAddr, std::chrono::system_clock::time_point> doing;
        std::set<NwkAddr> done;
        std::vector<std::function<void()>> observers;
        std::thread requestThread;
        std::mutex mutex;
        bool stop;
        std::function<void(ZDevice *)> observerCallback;

    public:
        TopologyCreation(SingletonObjects &singletonObjects) : singletonObjects(singletonObjects) {}

        ~TopologyCreation();

        void create();

        void addDevice(ZDevice *device);

        void addObserver(std::function<void()> observer);

    private:
        void manageRequest();

        void sleep(std::chrono::milliseconds duration) {
            std::unique_lock<std::mutex>(mutex);
            std::this_thread::sleep_for(duration);
        }

    };
}


#endif //DOMUS_ENGINE_TOPOLOGY_CREATION_H
