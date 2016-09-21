//
// Created by paolo on 19/09/16.
//

#ifndef DOMUS_ENGINE_SHOWDEVICEINFO_H
#define DOMUS_ENGINE_SHOWDEVICEINFO_H

#include "../RestParser/RestActions.h"
#include "../../Utils/DeviceInfoDispatcher.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {
        class ShowDeviceInfo : public ActionHandler, public DeviceInfoDispatcher::DeviceInfoObserver {
        public:
            ShowDeviceInfo(SingletonObjects &singletons) noexcept : singletons(singletons) {};
            ~ShowDeviceInfo();
            void operator()(const PlaceHolders &&placeHolder, ServerRequest &request,
                            Poco::Net::HTTPServerResponse &response);

            void newDeviceInfo(DeviceInfoMessage *) override ;
            void sendJSON(Poco::Net::HTTPServerResponse &response);
        private:
            SingletonObjects &singletons;
            bool resultPresent;
            zigbee::DeviceInfoMessage deviceInfoMessage;
            NwkAddr device;
        };
    }
}


#endif //DOMUS_ENGINE_SHOWDEVICEINFO_H
