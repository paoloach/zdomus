//
// Created by paolo on 29/12/16.
//

#include <boost/log/trivial.hpp>
#include "JSCallbackFifo.h"

namespace zigbee {
    using std::chrono::system_clock;

    void JSCallbackFifo::add(v8::Isolate *isolate, std::function<void(v8::Isolate *)> && fn) {
        std::lock_guard<std::mutex> lock(dataMutex);
        if (mutexes.count(isolate) == 0) {
            std::get<0>(mutexes[isolate]) = std::make_unique<std::mutex>();
            std::get<1>(mutexes[isolate]) = std::make_unique<std::condition_variable>();
        }
        std::get<1>(mutexes[isolate])->notify_all();
        fifo[isolate].push(fn);
    }

    void JSCallbackFifo::execute(v8::Isolate *isolate) {
        std::lock_guard<std::mutex> lock(dataMutex);
        auto & functions = fifo[isolate];
        while (!functions.empty()) {
            auto & function = functions.front();
            function(isolate);
            functions.pop();
        }
    }

    void JSCallbackFifo::execute(v8::Isolate *isolate, std::chrono::seconds timeToWait) {
        auto start = system_clock::now();
        execute(isolate);
        while (system_clock::now() - start < timeToWait) {
            waitFor(isolate, timeToWait);
            execute(isolate);
        }

    }

    void JSCallbackFifo::waitFor(v8::Isolate *isolate, std::chrono::seconds timeToWait) {
        if (mutexes.count(isolate) == 0) {
            std::get<0>(mutexes[isolate]) = std::make_unique<std::mutex>();
            std::get<1>(mutexes[isolate]) = std::make_unique<std::condition_variable>();
        }
        auto &signal = mutexes[isolate];
        std::unique_lock<std::mutex> lock(*std::get<0>(signal));
        std::get<1>(signal)->wait_for(lock, timeToWait);
    }

}
