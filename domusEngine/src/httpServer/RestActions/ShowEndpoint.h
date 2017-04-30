/*
 * ShowEndpoint.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWENDPOINT_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWENDPOINT_H_

#include "endpoint.h"
#include "router.h"

namespace zigbee {
    class SingletonObjects;
    namespace http {
        class ShowEndpoint {
        public:
            ShowEndpoint(SingletonObjects &singletons) noexcept : singletons(singletons) {};

            Net::Rest::Route::Result operator()(const Net::Rest::Request &request, Net::Http::ResponseWriter response);

        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWENDPOINT_H_ */
