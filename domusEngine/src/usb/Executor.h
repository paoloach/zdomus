//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_EXECUTOR_H
#define DOMUS_ENGINE_EXECUTOR_H

namespace zigbee {
    class Executor {
    public:
        virtual void operator()(unsigned char *data, int length) = 0;
    };
}


#endif //DOMUS_ENGINE_EXECUTOR_H
