//
// Created by paolo on 29/12/16.
//

#ifndef DOMUS_ENGINE_JSCALLBACKFIFO_H
#define DOMUS_ENGINE_JSCALLBACKFIFO_H

#include <boost/log/trivial.hpp>
#include <v8.h>
#include <tuple>
#include <queue>
#include <map>
#include <mutex>
#include <condition_variable>

namespace zigbee {
    class JSCallbackFifo {
        using signalData = std::tuple<std::unique_ptr<std::mutex>, std::unique_ptr<std::condition_variable>>;
    public:
        void add(v8::Isolate *isolate, std::function<void(v8::Isolate *)> && fn);

        void execute(v8::Isolate *isolate, std::chrono::seconds timeToWait);
    private:
        std::function<void(v8::Isolate *)> get(v8::Isolate *isolate);
        void execute(v8::Isolate *isolate);

        void waitFor(v8::Isolate * isolate, std::chrono::seconds timeToWait);

        size_t size(v8::Isolate * isolate)  {
            return fifo[isolate].size();
        }

    private:
        std::mutex dataMutex;
        std::map<v8::Isolate *, std::queue<std::function<void(v8::Isolate *)>>> fifo;
        std::map<v8::Isolate *, signalData > mutexes;
    };
}


#endif //DOMUS_ENGINE_JSCALLBACKFIFO_H
