//
// Created by paolo on 20/01/18.
//

#ifndef DOMUS_ENGINE_DELETEDEVICE_H
#define DOMUS_ENGINE_DELETEDEVICE_H

#include "endpoint.h"
#include "router.h"


namespace zigbee {
    class SingletonObjects;
    namespace http {
        class DeleteDevice {
        public:
            DeleteDevice(SingletonObjects *singletons) : singletons(singletons) {}

            Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

        private:
            SingletonObjects *singletons;
        };
    }
}


#endif //DOMUS_ENGINE_DELETEDEVICE_H
