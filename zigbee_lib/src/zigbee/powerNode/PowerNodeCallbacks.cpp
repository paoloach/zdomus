//
// Created by paolo on 15/05/17.
//

#include <boost/log/trivial.hpp>
#include "PowerNodeCallbacks.h"

using namespace boost::fibers;
using namespace std::chrono_literals;

zigbee::PowerNodeCallbacks::PowerNodeCallbacks() : callback([this]() {
    std::unique_lock<mutex> lk(this->mutexCond);
    while (true) {
        while(this->callbacks.empty()){
            boost::this_fiber::yield();
        }
        auto waitResult = this->cond.wait_for(lk, duration);
        BOOST_LOG_TRIVIAL(info) << "power node event";
        if (waitResult == boost::fibers::cv_status::timeout) {
            BOOST_LOG_TRIVIAL(info) << "power node timeout";
            while (!this->callbacks.empty()) {
                auto &&callback = this->callbacks.front();
                callback->timeout();
                this->callbacks.pop();
            }
        } else {
            while (!this->callbacks.empty()) {
                auto &&callback = this->callbacks.front();
                callback->response(this->powerNodeData);
                this->callbacks.pop();
            }
        }
    }
}), duration(60s) {
}


