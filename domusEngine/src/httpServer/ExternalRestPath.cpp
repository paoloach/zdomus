/*
 * FixedPathContainer.cpp
 *
 *  Created on: 09/apr/2015
 *      Author: Paolo Achdjian
 */

#include "ExternalRestPath.h"
#include <boost/log/trivial.hpp>
#include "../Exception/PathNotFound.h"
#include "RestParser/PlaceHolders.h"

namespace zigbee {
    namespace http {

        void ExternalRestPath::addRestValue(std::string &&stringPath, Callback &fn) {
            std::unique_lock<std::mutex> uniqueLock(mutexRestValue);
            RestPath restPath(stringPath);
            for (auto &path: mapRestValue) {
                if (std::get<0>(path) == restPath){
                    std::get<1>(path) = fn;
                    BOOST_LOG_TRIVIAL(info) << "update path: " << stringPath;
                    return;
                }
            }
            BOOST_LOG_TRIVIAL(info) << "add path: " << stringPath;
            mapRestValue.emplace_back(std::move(restPath), fn);
        }

        std::tuple<std::string, bool> ExternalRestPath::getValue(const PathReceived &pathReceived) {
            std::unique_lock<std::mutex> uniqueLock(mutexRestValue);
            BOOST_LOG_TRIVIAL(info) << "find for  path: " << (std::string) pathReceived;
            for (auto &path: mapRestValue) {
                if (std::get<0>(path) == pathReceived) {
                    PlaceHolders placeHolders(std::get<0>(path), pathReceived);

                    return std::make_tuple(std::get<1>(path)(placeHolders.getPlaceholders()), true);
                }
            }
            return std::make_tuple("", false);
        }

    } /* namespace http */
} /* namespace zigbee */
