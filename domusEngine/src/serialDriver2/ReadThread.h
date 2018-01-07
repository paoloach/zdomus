//
// Created by paolo on 20/12/17.
//

#ifndef DOMUS_ENGINE_READTHREAD_H
#define DOMUS_ENGINE_READTHREAD_H

#include "SerialDriver2.h"

namespace zigbee {
    void readThread(SingletonObjects * singletonObjects, int serialFd);
}


#endif //DOMUS_ENGINE_READTHREAD_H
