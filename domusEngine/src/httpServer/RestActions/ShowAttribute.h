/*
 * ShowAttribute.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_

#include "../RestParser/RestActions.h"
#include "ClusterThrowingException.h"
#include <atomic>
#include <zcl/ZCLAttribute.h>

namespace zigbee {

  class SingletonObjects;

  namespace http {

    class PlaceHolders;

    class ShowAttribute : public ActionHandler, public ClusterThrowingException {
    private:
        std::atomic_bool attributeArrived;
        int status;
    public:
        ShowAttribute(SingletonObjects &singletons) noexcept : singletons(singletons) { std::atomic_init(&attributeArrived, false);};

        void operator()(const PlaceHolders &&placeHolder, Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
        void attributeReceived(int status);
        void send(Poco::Net::HTTPServerResponse &response, std::shared_ptr<ZCLAttribute> attribute);
    private:
        SingletonObjects &singletons;
    };

  } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_ */
