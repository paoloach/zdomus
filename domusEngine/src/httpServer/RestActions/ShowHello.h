/*
 * ShowHello.h
 *
 *  Created on: 27/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWHELLO_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWHELLO_H_

#include "endpoint.h"
#include "router.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class PlaceHolders;

        class ShowHello  {
        public:
            ShowHello() noexcept { };

            Net::Rest::Route::Result operator()(const Net::Rest::Request& request, Net::Http::ResponseWriter && response);
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWHELLO_H_ */
