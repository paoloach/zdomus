/*
 * ShowDevices.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICES_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICES_H_

#include "endpoint.h"
#include "router.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class ShowDevices {
        public:
            ShowDevices(SingletonObjects &singletons) noexcept : singletons(singletons) { };

            Pistache::Rest::Route::Result  operator()(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter  && response);
        private:
            SingletonObjects &singletons;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICES_H_ */
