//
// Created by paolo on 19/09/16.
//

#ifndef DOMUS_ENGINE_SHOWDEVICEINFO_H
#define DOMUS_ENGINE_SHOWDEVICEINFO_H

#include "endpoint.h"
#include "router.h"

#include "../../Utils/DeviceInfoDispatcher.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {
        class ShowDeviceInfo :  public DeviceInfoDispatcher::DeviceInfoObserver {
        public:
            ShowDeviceInfo(SingletonObjects &singletons) noexcept : singletons(singletons) {};
            ~ShowDeviceInfo();
            Net::Rest::Route::Result  operator()(const Net::Rest::Request& request, Net::Http::ResponseWriter  && response);
            void newDeviceInfo(DeviceInfoMessage *) override ;
            void sendJSON(Net::Http::ResponseWriter &response);
        private:
            SingletonObjects &singletons;
            bool resultPresent;
            zigbee::DeviceInfoMessage deviceInfoMessage;
            NwkAddr device;
        };
    }
}


#endif //DOMUS_ENGINE_SHOWDEVICEINFO_H
