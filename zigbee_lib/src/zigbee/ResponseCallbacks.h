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
        ResponseCallbacks(std::chrono::seconds timeout) : stop(false),callback([this]() { this->fiberCallback(); }), duration(timeout) {

        }


        ResponseCallbacks(ResponseCallbacks && other) :
                stop(false),
                data(std::move(other.data)),
                callback([this]() { this->fiberCallback(); }),
                duration(other.duration) {
            callbacks.swap(other.callbacks);
            other.stop=true;
            other.callback.join();
        }

        ResponseCallbacks(std::chrono::seconds timeout, std::unique_ptr <ResponseCallback<T>> &&callback) : stop(false),callback([this]() { this->fiberCallback(); }), duration(timeout) {
                callbacks.push(std::move(callback));
        }

        void fiberCallback() {
            std::unique_lock <boost::fibers::mutex> lk(this->mutexCond);
            while (!stop) {
                while (this->callbacks.empty()) {
                    boost::this_fiber::yield();
                    if (stop ){
                        return;
                    }
                }
                auto waitResult = this->cond.wait_for(lk, duration);
                if (waitResult == boost::fibers::cv_status::timeout) {
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
        bool stop;
        T data;
        std::queue <std::unique_ptr<ResponseCallback<T>>> callbacks;
        boost::fibers::condition_variable cond;
        boost::fibers::mutex mutexCond;
        boost::fibers::fiber callback;
        std::chrono::seconds duration;
    };
}
#endif //ZIGBEE_LIB_RESPONSECALLBACKS_H
