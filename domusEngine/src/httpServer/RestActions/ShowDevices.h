/*
 * ShowDevices.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICES_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICES_H_

#include "pistache/endpoint.h"
#include "pistache/router.h"
#include "../../Utils/SingletonObjects.h"

namespace zigbee::http {
    class ShowDevices {
    public:
        ShowDevices(SingletonObjects *singletons) noexcept : singletons(singletons) {};

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

    private:
        SingletonObjects *singletons;
    };
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWDEVICES_H_ */
