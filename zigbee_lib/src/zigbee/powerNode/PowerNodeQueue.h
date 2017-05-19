//
// Created by paolo on 14/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODEQUEUE_H
#define DOMUS_ENGINE_POWERNODEQUEUE_H

#include <queue>
#include <boost/fiber/mutex.hpp>
#include <boost/fiber/unbuffered_channel.hpp>
#include "../NwkAddr.h"
#include "PowerNodeCallbacks.h"


namespace zigbee {
    class PowerNodeQueue {
    public:
        using PowerNodeResponseCallback = std::function<void(std::shared_ptr<PowerNodeData> powerNode)>;
        using PowerNodeChannel = boost::fibers::unbuffered_channel< std::tuple<NwkAddr, PowerNodeResponseCallback > >;
        void add(NwkAddr nwkAddr, PowerNodeResponseCallback && callback) {
            powerNodeChannel.push(std::make_tuple(nwkAddr, std::move(callback)));
        }

        bool empty() const { return powerNodeCallbacks.empty(); }

        void setPowerNode(std::shared_ptr<PowerNodeData> &powerNodeData) {
            if (powerNodeCallbacks.count(powerNodeData->nwkAddr) > 0) {
                powerNodeCallbacks[powerNodeData->nwkAddr].setPowerNode(powerNodeData);
            }
        }

        void startDequeFiber();

    private:
        std::map<NwkAddr, PowerNodeCallbacks> powerNodeCallbacks;
        boost::fibers::fiber dequeFiber;
        PowerNodeChannel powerNodeChannel;
    };
}

#endif //DOMUS_ENGINE_POWERNODEQUEUE_H
