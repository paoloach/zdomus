/*
 * ExecuteCmd.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_EXECUTECMD_H_
#define SRC_HTTPSERVER_RESTACTIONS_EXECUTECMD_H_

#include "ClusterThrowingException.h"
#include "../../Utils/SingletonObjects.h"

namespace zigbee::http {
    class PlaceHolders;

    class ExecuteCmd : public ClusterThrowingException {
    public:
        ExecuteCmd(SingletonObjects *singletons) noexcept : singletons(singletons) { };

        Pistache::Rest::Route::Result operator()(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter  && response);

    private:
        SingletonObjects* singletons;
    };

} /* namespace zigbee::http */

#endif /* SRC_HTTPSERVER_RESTACTIONS_EXECUTECMD_H_ */
