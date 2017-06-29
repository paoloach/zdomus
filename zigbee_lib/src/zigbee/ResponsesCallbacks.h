//
// Created by paolo on 6/26/17.
//

#ifndef ZIGBEE_LIB_RESPONSESCALLBACKS_H
#define ZIGBEE_LIB_RESPONSESCALLBACKS_H

#include <chrono>
#include <list>
#include <thread>
#include <boost/fiber/fiber.hpp>
#include "ResponseCallbacks.h"


namespace zigbee {
    template<typename K, typename T>
    class ResponsesCallbacks {
    private:
        struct Value {
            Value(K k, ResponseCallbacks<T> && responseCallbacks):key(k), responseCallbacks(std::move(responseCallbacks)){}
            K key;
            ResponseCallbacks<T> responseCallbacks;
        };
    public:
        ResponsesCallbacks(std::chrono::seconds timeout) : timeout{timeout} {}

        void add(K k, std::unique_ptr<ResponseCallback<T>> && callback) {
            for(auto & value: elements){
                if (value.key == k){
                    value.responseCallbacks.addCallback(std::move(callback));
                    return;
                }
            }
            elements.emplace_back(k, ResponseCallbacks<T>(timeout));
            elements.back().responseCallbacks.addCallback(std::move(callback));
        }

        void setData(K k, T data){
            for(auto & value: elements){
                if (value.key == k){
                    value.responseCallbacks.setData(data);
                    return;
                }
            }
        }

        bool empty() const {
            return elements.empty();
        }


    private:
        std::chrono::seconds timeout;
        std::list<Value> elements;
    };

}

#endif //ZIGBEE_LIB_RESPONSESCALLBACKS_H
