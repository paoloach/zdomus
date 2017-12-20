//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_SHOWBINDTABLE_H
#define DOMUS_ENGINE_SHOWBINDTABLE_H

#include "endpoint.h"
#include "router.h"

namespace zigbee {

    class SingletonObjects;
    namespace http {

        class ShowBindTable  {
        public:
            ShowBindTable(zigbee::SingletonObjects &singletons) noexcept : singletons(singletons) { };
            Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter  && response);

        private:
            SingletonObjects &singletons;
        };
    }
}


#endif //DOMUS_ENGINE_SHOWBINDTABLE_H
