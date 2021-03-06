//
// Created by paolo on 19/09/16.
//

#ifndef DOMUS_ENGINE_SHOWDEVICEINFO_H
#define DOMUS_ENGINE_SHOWDEVICEINFO_H

#include "pistache/endpoint.h"
#include "pistache/router.h"

#include "../../Utils/DeviceInfoDispatcher.h"
#include "../../Utils/SingletonObjects.h"

namespace zigbee {
    namespace http {
        class ShowDeviceInfo :  public DeviceInfoDispatcher::DeviceInfoObserver {
        public:
            ShowDeviceInfo(SingletonObjects *singletons) noexcept : singletons(singletons) {};
            ~ShowDeviceInfo();
            Pistache::Rest::Route::Result  operator()(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter  && response);
            void newDeviceInfo(DeviceInfoMessage *) override ;
            void sendJSON(Pistache::Http::ResponseWriter &response);
        private:
            SingletonObjects *singletons;
            bool resultPresent;
            zigbee::DeviceInfoMessage deviceInfoMessage;
            NwkAddr device;
        };
    }
}


#endif //DOMUS_ENGINE_SHOWDEVICEINFO_H
