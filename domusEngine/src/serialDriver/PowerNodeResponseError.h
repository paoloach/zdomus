//
// Created by paolo on 23/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPONSEERROR_H
#define DOMUS_ENGINE_POWERNODERESPONSEERROR_H

#include "SerialExecutor.h"

namespace zigbee {
    class SingletonObjectsImpl;

    class PowerNodeResponseError : public SerialExecutor {
    public:
        PowerNodeResponseError(SingletonObjectsImpl &singletons) : singletons(singletons) {}

        /// NPRE: networkdId, status
        //       4digit       2Digit
        void operator()(const std::string &msg) override;

    private:
        SingletonObjectsImpl &singletons;
    };
}


#endif //DOMUS_ENGINE_POWERNODERESPONSEERROR_H
