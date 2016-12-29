//
// Created by paolo on 29/12/16.
//

#ifndef DOMUS_ENGINE_JSCALLBACKFIFO_H
#define DOMUS_ENGINE_JSCALLBACKFIFO_H

#include <v8.h>
#include <queue>
#include <map>

namespace zigbee {

    static void emptyFn(v8::Isolate *){}

    class JSCallbackFifo {
    public:
        void add(v8::Isolate *isolate, std::function<void(v8::Isolate *)> &&fn) {

            fifo[isolate].push(fn);
        }

        std::function<void(v8::Isolate *)> get(v8::Isolate *isolate) {
            if (fifo.count(isolate) > 0 && fifo[isolate].size() > 0) {
                std::function<void(v8::Isolate *)> fn = fifo[isolate].front();
                fifo[isolate].pop();
                return fn;
            } else {
                return emptyFn;
            }
        }

        size_t size(v8::Isolate * isolate)  {
            return fifo[isolate].size();
        }

    private:
        std::map<v8::Isolate *, std::queue<std::function<void(v8::Isolate *)>>> fifo;
    };
}


#endif //DOMUS_ENGINE_JSCALLBACKFIFO_H
