/*
 * RestPath.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */
#include <boost/filesystem/path.hpp>
#include "RestPath.h"

namespace zigbee {
    namespace http {

        RestPath::RestPath(const std::string &uri) noexcept {
            boost::filesystem::path path(uri);
            for (auto element : path) {
                if (element != "/" && element != "\\")
                    elements.push_back(element.string());
            }
        }

        RestPath::RestPath(RestPath &&other) noexcept: elements(std::move(other.elements)) {
        }

        RestPath::RestPath(const RestPath &other) noexcept: elements(other.elements) {
        }

        bool RestPath::operator==(const PathReceived &pathReceived) const noexcept {
            if (pathReceived.getSize() == elements.size()) {
                auto receivedElem = pathReceived.begin();
                auto pathElemen = elements.begin();
                while (pathElemen != elements.end()) {
                    if (!pathElemen->isPlaceholder()) {
                        if (pathElemen->getValue() != *receivedElem) {
                            return false;
                        }
                    }
                    receivedElem++;
                    pathElemen++;

                }
                return true;
            } else {
                return false;
            }
        }

        bool RestPath::operator==(const RestPath &other) const noexcept {
            return elements == other.elements;
        }

        std::vector<std::string> RestPath::getAllPlaceholders() {
            std::vector<std::string> placeholders;
            for(auto & element: elements){
                if (element.isPlaceholder()){
                    placeholders.push_back(element.getValue());
                }
            }
            return placeholders;
        }

    } /* namespace http */
} /* namespace zigbee */

