//
// Created by paolo on 29/12/16.
//

#ifndef DOMUS_ENGINE_JSCALLBACKFIFO_H
#define DOMUS_ENGINE_JSCALLBACKFIFO_H

#include <v8.h>
#include <queue>

namespace zigbee {

    class JSCallbackFifo {
    public:
        void add(std::function<void(v8::Isolate *)> && fn ) {
            fifo.push(fn);
        }

        std::function<void(v8::Isolate *)> get() {
            std::function<void(v8::Isolate *)> fn = fifo.front();
            fifo.pop();
            return fn;
        }

        size_t size() const {
            return fifo.size();
        }

    private:
        std::queue<std::function<void(v8::Isolate *)>> fifo;
    };
}


#endif //DOMUS_ENGINE_JSCALLBACKFIFO_H
