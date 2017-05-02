//
// Created by paolo on 10/05/16.
//

#ifndef DOMUS_ENGINE_SHOWATTRIBUTEFACTORY_H
#define DOMUS_ENGINE_SHOWATTRIBUTEFACTORY_H

#include "endpoint.h"
#include "router.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {
        class ShowAttributeFactory {
        public:
            ShowAttributeFactory(SingletonObjects &singletons) : singletons(singletons) {}

            Net::Rest::Route::Result operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter && response);

        private:
            SingletonObjects &singletons;
        };
    }
}

#endif //DOMUS_ENGINE_SHOWATTRIBUTEFACTORY_H
