//
// Created by paolo on 23/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPONSEERROR_H
#define DOMUS_ENGINE_POWERNODERESPONSEERROR_H

#include "SerialExecutor.h"

namespace zigbee {
    class SingletonObjects;

    class PowerNodeResponseError : public SerialExecutor {
    public:
        PowerNodeResponseError(SingletonObjects *singletons) : singletons(singletons) {}

        /// NPRE: networkdId, status
        //       4digit       2Digit
        void operator()(const std::string &msg) override;

    private:
        SingletonObjects *singletons;
    };
}


#endif //DOMUS_ENGINE_POWERNODERESPONSEERROR_H
