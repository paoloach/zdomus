/*
 * ShowAttribute.h
 *
 *  Created on: 26/giu/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_
#define SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_

#include <algorithm>
#include <atomic>
#include <zcl/ZCLAttribute.h>
#include <zigbee/AttributesResponseCallback.h>
#include <zigbee/AttributesKey.h>
#include <iostream>

#include <boost/log/trivial.hpp>


#include "endpoint.h"
#include "router.h"
#include "ClusterThrowingException.h"

namespace zigbee {

    class SingletonObjects;

    namespace http {

        class ShowAttribute : public ClusterThrowingException , public AttributesResponseCallback {

        public:
            ShowAttribute(SingletonObjects &singletons,const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter && response);
            virtual ~ShowAttribute() = default;
            AttributesKey key;
        private:
            void response(std::vector<ZCLAttribute *> && attributes ) override;
            bool allTimeout(std::vector<ZCLAttribute *> & attributes) {
                return std::find_if(attributes.begin(), attributes.end(), [](ZCLAttribute * attribute){return attribute != nullptr;}) ==attributes.end();
            }
            SingletonObjects &singletons;
            Pistache::Http::ResponseWriter responseWriter;

        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTACTIONS_SHOWATTRIBUTE_H_ */
