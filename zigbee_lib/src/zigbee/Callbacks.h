//
// Created by paolo on 01/06/17.
//

#ifndef ZIGBEE_LIB_CALLBACKS_H
#define ZIGBEE_LIB_CALLBACKS_H

#include <queue>
#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/mutex.hpp>
#include "ResponseCallback.h"


namespace zigbee {
    template <typename T>
    class Callbacks {
        Callbacks() : callback([this]() {
                std::unique_lock<boost::fibers::mutex> lk(this->mutexCond);
                while (true) {
                    while(this->callbacks.empty()){
                        boost::this_fiber::yield();
                    }
                    auto waitResult = this->cond.wait_for(lk, duration);
                    BOOST_LOG_TRIVIAL(info) << "event";
                    if (waitResult == boost::fibers::cv_status::timeout) {
                        BOOST_LOG_TRIVIAL(info) << "event timeout";
                        while (!this->callbacks.empty()) {
                            auto &&callback = this->callbacks.front();
                            callback->timeout();
                            this->callbacks.pop();
                        }
                    } else {
                        while (!this->callbacks.empty()) {
                            auto &&callback = this->callbacks.front();
                            callback->response(this->data);
                            this->callbacks.pop();
                        }
                    }
                }
            }), duration(60s) {
        };

        void addCallback( std::unique_ptr<ResponseCallback<T>> && callback){
            callbacks.push(std::move(callback));
        }
        void setPowerNode(T data){
            this->data = data;
            cond.notify_all();
        }
    private:
        T data;
        std::queue<std::unique_ptr<ResponseCallback<T> > > callbacks;
        boost::fibers::condition_variable cond;
        boost::fibers::mutex  mutexCond;
        boost::fibers::fiber  callback;
        std::chrono::seconds duration;
    };
}


#endif //ZIGBEE_LIB_CALLBACKS_H
