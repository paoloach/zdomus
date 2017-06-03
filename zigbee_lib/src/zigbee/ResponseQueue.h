//
// Created by paolo on 01/06/17.
//

#ifndef ZIGBEE_LIB_RESPONSEQUEUE_H
#define ZIGBEE_LIB_RESPONSEQUEUE_H


#include <queue>
#include <tuple>
#include <boost/fiber/mutex.hpp>
#include <boost/fiber/unbuffered_channel.hpp>
#include <boost/fiber/fiber.hpp>
#include "NwkAddr.h"
#include "ResponseCallbacks.h"


namespace zigbee {
    template <typename K, typename  T>
    class ResponseQueue {
    public:
        using Channel = boost::fibers::unbuffered_channel< std::tuple<K, std::unique_ptr<ResponseCallback<T>> > > ;
        void add(K key, std::unique_ptr<ResponseCallback<T>> && callback) {
            channel.push(std::make_tuple(key, std::move(callback)));
        }

        bool empty() const { return callbacks.empty(); }

        void setData(K key, T data) {
            if (callbacks.count(key) > 0) {
                callbacks[key].setData(data);
            }
        }

        void startDequeFiber(){
            dequeFiber =  boost::fibers::fiber([this](){
                for(auto && data: channel){
                    auto & callback = callbacks[std::get<K>(data)];
                    callback.addCallback(std::move(std::get<std::unique_ptr<ResponseCallback<T>> >(data)));
                }
            });
        }

    private:
        std::map<K, ResponseCallbacks<T>> callbacks;
        boost::fibers::fiber dequeFiber;
        Channel channel;
    };
}


#endif //ZIGBEE_LIB_RESPONSEQUEUE_H
