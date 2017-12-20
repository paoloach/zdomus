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
            Pistache::Rest::Route::Result  operator()(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter  && response);
            void newDeviceInfo(DeviceInfoMessage *) override ;
            void sendJSON(Pistache::Http::ResponseWriter &response);
        private:
            SingletonObjects &singletons;
            bool resultPresent;
            zigbee::DeviceInfoMessage deviceInfoMessage;
            NwkAddr device;
        };
    }
}


#endif //DOMUS_ENGINE_SHOWDEVICEINFO_H
