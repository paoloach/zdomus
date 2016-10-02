//
// Created by paolo on 23/09/16.
//

#ifndef DOMUS_ENGINE_IEEEADDRESSRESPONSE_H
#define DOMUS_ENGINE_IEEEADDRESSRESPONSE_H

#include <boost/endian/conversion.hpp>
#include "../ZigbeeData/IEEEAddressResponse.h"
#include "Executor.h"
#include "../Utils/SingletonObjects.h"

namespace zigbee {
        class IEEEAddressResponseExecutor : public Executor {
    private:
        SingletonObjects &singletonObjects;

    public:
        IEEEAddressResponseExecutor(SingletonObjects &singletonObjects) : singletonObjects{singletonObjects} {}

        // receive
        // msg code (1 byte)
        // ieeeAddr(8 bytes)
        // nwkaddr (2 bytes)
        // assDevices (1 bytes)
        // startIndex (1  byte)
        // nwkAddrss child list (2*assDevices bytes)
        virtual void operator()(unsigned char *data, int ) override {
            IEEEAddrResp message;

            data++;
            message.ieeeAddr = ExtAddress(data);
            data+=Z_EXTADDR_LEN;
            message.nwkAddr.setId( boost::endian::little_to_native(*(uint16_t *) data));
            data+=2;
            uint32_t count = *data++;
            message.startIndex = *data++;
            while(count != 0){
                count--;
                message.children.emplace(boost::endian::little_to_native(*(uint16_t *) data));
            }

            singletonObjects.getZDevices()->addDeviceInfo(message);
        }
    };

}


#endif //DOMUS_ENGINE_IEEEADDRESSRESPONSE_H
