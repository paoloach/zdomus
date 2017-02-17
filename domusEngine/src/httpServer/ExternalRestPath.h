/*
 * FixedPathContainer.h
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_FIXEDPATHCONTAINER_H_
#define SRC_HTTPSERVER_FIXEDPATHCONTAINER_H_

#include <map>
#include <mutex>

#include "../httpServer/RestParser/PathReceived.h"
#include "RestParser/RestPath.h"

namespace zigbee {
    namespace http {

        class ExternalRestPath {
        public:
            using CallbackArgs = std::vector<std::tuple<std::string, std::string>>;
            using Callback = std::function<std::string(CallbackArgs &&)>;

            void addRestValue(std::string &&path, Callback &fn);

            std::tuple<std::string, bool> getValue(const PathReceived &path);

        private:
            std::vector<std::tuple<RestPath, Callback> > mapRestValue;
            std::mutex mutexRestValue;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_FIXEDPATHCONTAINER_H_ */
