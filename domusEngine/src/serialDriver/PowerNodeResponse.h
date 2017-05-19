//
// Created by paolo on 11/05/17.
//

#ifndef DOMUS_ENGINE_POWERNODERESPONSE_H
#define DOMUS_ENGINE_POWERNODERESPONSE_H


#include "SerialExecutor.h"

namespace zigbee {
    class SingletonObjects;
    class PowerNodeResponse : public SerialExecutor {
    public:
        PowerNodeResponse(SingletonObjects &singletons) : singletons(singletons) {}

        /// NPR: networkdId, powerMode, availablePowerSources, currentPowerSource, currentPowerSourceLevel
        //       4digit       1Digit        1Digit               1Digit                1Digit
        virtual void operator()(const std::string &msg) override;

    private:
        SingletonObjects &singletons;
    };
}


#endif //DOMUS_ENGINE_POWERNODERESPONSE_H
