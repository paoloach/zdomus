//
// Created by paolo on 02/06/17.
//

#ifndef ZIGBEE_LIB_RESPONSECALLBACKS_H
#define ZIGBEE_LIB_RESPONSECALLBACKS_H

#include <queue>
#include <boost/fiber/condition_variable.hpp>
#include <boost/log/trivial.hpp>

#include "ResponseCallback.h"

namespace zigbee {
    using namespace std::chrono_literals;
    template<typename T>
    class ResponseCallbacks {
    public:
        ResponseCallbacks() : callback([this]() { this->fiberCallback(); }), duration(60s) {

        }

        void fiberCallback() {
            std::unique_lock <boost::fibers::mutex> lk(this->mutexCond);
            while (true) {
                while (this->callbacks.empty()) {
                    boost::this_fiber::yield();
                }
                auto waitResult = this->cond.wait_for(lk, duration);
                BOOST_LOG_TRIVIAL(info) << "data event";
                if (waitResult == boost::fibers::cv_status::timeout) {
                    BOOST_LOG_TRIVIAL(info) << "data timeout";
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
        }

        void addCallback(std::unique_ptr <ResponseCallback<T>> &&callback) {
            callbacks.push(std::move(callback));
        }

        void setData(T data) {
            this->data = data;
            cond.notify_all();
        }

    private:
        T data;
        std::queue <std::unique_ptr<ResponseCallback<T>>> callbacks;
        boost::fibers::condition_variable cond;
        boost::fibers::mutex mutexCond;
        boost::fibers::fiber callback;
        std::chrono::seconds duration;
    };
}
#endif //ZIGBEE_LIB_RESPONSECALLBACKS_H
