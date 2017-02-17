/*
 * PlaceHolders.cpp
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <utility>
#include <boost/log/trivial.hpp>

#include "Exceptions/PlaceholderNotFound.h"
#include "PlaceHolders.h"

namespace zigbee {
    namespace http {

        PlaceHolders::PlaceHolders(RestPath &&restPath, PathReceived &&pathReceived) noexcept : restPath(std::move(restPath)), pathReceived(std::move(pathReceived)) {

        }

        PlaceHolders::PlaceHolders(const RestPath &restPath, PathReceived &&pathReceived) noexcept : restPath(std::move(restPath)), pathReceived(std::move(pathReceived)) {
        }

        std::string PlaceHolders::getInternal(std::string &&placeHolder) const {
            auto receivedElem = pathReceived.begin();
            auto pathElemen = restPath.begin();

            BOOST_LOG_TRIVIAL(info) << "placeHolder = " << placeHolder;

            while (pathElemen != restPath.end()) {
                if (pathElemen->isPlaceholder()) {
                    if (pathElemen->getValue() == placeHolder) {
                        return *receivedElem;
                    }
                }
                receivedElem++;
                pathElemen++;

            }
            throw PlaceholderNotFound {};
        }

        PlaceHolders::PlaceHolders(const RestPath restPath, PathReceived pathReceived)  noexcept : restPath(std::move(restPath)), pathReceived(std::move(pathReceived)) {

        }

        std::vector<std::tuple<std::string, std::string>> PlaceHolders::getPlaceholders() {
            std::vector<std::tuple<std::string, std::string>> result;

            for (auto name: restPath.getAllPlaceholders()) {
                result.emplace_back(name, getInternal(std::move(name)));
            }

            return result;
        }

    } /* namespace http */
} /* namespace zigbee */

