//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_SHOWBINDTABLE_H
#define DOMUS_ENGINE_SHOWBINDTABLE_H

#include "pistache/endpoint.h"
#include "pistache/router.h"

namespace zigbee {

    class SingletonObjects;
    namespace http {

        class ShowBindTable  {
        public:
            ShowBindTable(zigbee::SingletonObjects &singletons) noexcept : singletons(singletons) { };
            Net::Rest::Route::Result operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response);

        private:
            SingletonObjects &singletons;
        };
    }
}


#endif //DOMUS_ENGINE_SHOWBINDTABLE_H
