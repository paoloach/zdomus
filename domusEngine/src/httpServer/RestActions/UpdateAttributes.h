//
// Created by paolo on 23/06/16.
//

#ifndef DOMUS_ENGINE_UPDATEATTRIBUTES_H
#define DOMUS_ENGINE_UPDATEATTRIBUTES_H

#include "endpoint.h"
#include "router.h"
#include "ClusterThrowingException.h"

namespace zigbee {
    class SingletonObjects;
    namespace http {

        class UpdateAttributes : public ClusterThrowingException{
        public:
            UpdateAttributes(SingletonObjects &singletons) noexcept : singletons(singletons) { };

            Net::Rest::Route::Result operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response);

        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */


#endif //DOMUS_ENGINE_UPDATEATTRIBUTES_H
