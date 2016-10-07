/*
 * RestPath.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_RESTPATH_H_
#define SRC_HTTPSERVER_RESTPARSER_RESTPATH_H_

#include <vector>

#include "PathReceived.h"
#include "PathElement.h"

namespace zigbee {
    namespace http {

        class RestPath {
        private:
            std::vector<PathElement> elements;
        public:
            RestPath(const std::string &uri) noexcept;

            RestPath(RestPath &&other) noexcept;

            RestPath(const RestPath &other) noexcept;

            RestPath() = default;

        public:
            bool operator==(const PathReceived &pathReceived) const noexcept;

            auto begin() const noexcept -> decltype(elements.begin()) { return elements.begin(); }

            auto end() const noexcept -> decltype(elements.end()) { return elements.end(); }
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_RESTPATH_H_ */
