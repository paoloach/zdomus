/*
 * ShowOutCluster.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWOUTCLUSTER_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWOUTCLUSTER_H_

#include "endpoint.h"
#include "router.h"
#include "../../Utils/SingletonObjects.h"

namespace zigbee::http {
    class ShowOutCluster {
    public:
        ShowOutCluster(SingletonObjects *singletons) noexcept : singletons(singletons) {};

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter &&response);

    private:
        SingletonObjects *singletons;
    };
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWOUTCLUSTER_H_ */
