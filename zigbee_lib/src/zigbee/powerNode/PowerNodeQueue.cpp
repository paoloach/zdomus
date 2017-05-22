//
// Created by paolo on 14/05/17.
//

#include <boost/log/trivial.hpp>
#include "PowerNodeQueue.h"
namespace  zigbee {
    using namespace std::chrono_literals;
    void PowerNodeQueue::startDequeFiber() {
        dequeFiber =  boost::fibers::fiber([this](){
            for(auto && data: powerNodeChannel){
                auto & powerNodeCallback = powerNodeCallbacks[std::get<NwkAddr>(data)];
                powerNodeCallback.addCallback(std::move(std::get<std::unique_ptr<PowerNodeResponseCallback> >(data)));
            }
        });
    }

}
