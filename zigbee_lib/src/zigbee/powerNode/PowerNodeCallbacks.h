//
// Created by paolo on 15/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODECALLBACKS_H
#define DOMUS_ENGINE_POWERNODECALLBACKS_H

#include <queue>
#include <boost/fiber/condition_variable.hpp>
#include "../PowerNodeData.h"
#include "PowerNodeResponseCallback.h"

namespace zigbee {
    class PowerNodeCallbacks {
    public:
        PowerNodeCallbacks();

        void addCallback( std::unique_ptr<PowerNodeResponseCallback> && callback){
            callbacks.push(std::move(callback));
        }
        void setPowerNode(std::shared_ptr<PowerNodeData> powerNodeData){
            this->powerNodeData = powerNodeData;
            cond.notify_all();
        }
    private:
        std::shared_ptr<PowerNodeData> powerNodeData;
        std::queue<std::unique_ptr<PowerNodeResponseCallback>> callbacks;
        boost::fibers::condition_variable cond;
        boost::fibers::mutex  mutexCond;
        boost::fibers::fiber  callback;
        std::chrono::seconds duration;
    };
}

#endif //DOMUS_ENGINE_POWERNODECALLBACKS_H