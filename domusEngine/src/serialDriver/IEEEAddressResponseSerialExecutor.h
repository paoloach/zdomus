//
// Created by paolo on 01/01/17.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H


#include <zigbee/messageStructure/IEEEAddressResponse.h>
#include "SerialExecutor.h"



namespace zigbee {
    class SingletonObjects;
    class IEEEAddressResponseSerialExecutor : public SerialExecutor {
    public:
        IEEEAddressResponseSerialExecutor(SingletonObjects * singletonObjects) : singletonObjects(singletonObjects) {}

        // IE: ieeeaddress, networkAddress, numChild, firstChildNwkId, ..., lastChildNwkId
        //      16digits ,     4digits,      2digits,  4digits,      , ...,  4digits
        void operator()(const std::string &msg) override;

    private:
        SingletonObjects * singletonObjects;
    };
}

#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSESERIALEXECUTOR_H
