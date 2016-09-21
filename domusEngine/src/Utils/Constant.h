//
// Created by paolo on 20/09/16.
//

#ifndef DOMUS_ENGINE_CONSTANT_H
#define DOMUS_ENGINE_CONSTANT_H


#include <chrono>
namespace  zigbee {
    class Constant {
    public:
        Constant();
        std::chrono::duration<int64_t> requestTimeout;

    };
}


#endif //DOMUS_ENGINE_CONSTANT_H
