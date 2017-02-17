/*
 * PathReceived.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_PATHRECEIVED_
#define SRC_HTTPSERVER_RESTPARSER_PATHRECEIVED_

#include <string>
#include <vector>
#include <map>
#include "RestQuery.h"

namespace zigbee {
    namespace http {

        class PathReceived {
        private:
            using QueryParams = std::map<std::string, RestQuery>;
            std::vector<std::string> elements;
            QueryParams queryParams;
        public:
            PathReceived() = default;

            PathReceived(std::string &&uri) noexcept;

            PathReceived(PathReceived &&other) = default;

            PathReceived(const PathReceived &other) = default;

            auto begin() const noexcept -> decltype(elements.begin()) { return elements.begin(); }

            auto end() const noexcept -> decltype(elements.end()) { return elements.end(); }

            auto getSize() const noexcept -> decltype(elements.size()) { return elements.size(); }

            auto getQueryParams() const noexcept -> decltype(queryParams) { return queryParams; }

            operator std::string() const;

            friend bool operator==(const zigbee::http::PathReceived &, const zigbee::http::PathReceived &);

            friend bool operator<(const zigbee::http::PathReceived &, const zigbee::http::PathReceived &);

        private:
            void createElements(std::string &&uri);

            void init(std::string &&uri) noexcept;

        };

    }  // end http
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_PATHRECEIVED_ */
