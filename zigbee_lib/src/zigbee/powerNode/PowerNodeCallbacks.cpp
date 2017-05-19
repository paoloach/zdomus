//
// Created by paolo on 15/05/17.
//

#include <boost/log/trivial.hpp>
#include "PowerNodeCallbacks.h"

using namespace boost::fibers;

zigbee::PowerNodeCallbacks::PowerNodeCallbacks() : callback([this]() {
    std::unique_lock<mutex> lk(this->mutexCond);
    while (true) {
        this->cond.wait(lk);
        BOOST_LOG_TRIVIAL(info) << "power node event";
        while (!this->callbacks.empty()) {
            this->callbacks.front()(this->powerNodeData);
            this->callbacks.pop();
        }
    }
}) {
}


