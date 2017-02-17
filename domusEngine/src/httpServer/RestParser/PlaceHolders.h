/*
 * PlaceHolders.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_PLACEHOLDERS_H_
#define SRC_HTTPSERVER_RESTPARSER_PLACEHOLDERS_H_

#include <boost/lexical_cast.hpp>
#include <zigbee/ZigbeeTypes.h>

#include "RestPath.h"
#include "PathReceived.h"
#include "Exceptions/QueryParamNotFound.h"

namespace zigbee {
    namespace http {

        class PlaceHolders {
        public:
            PlaceHolders() = default;
            PlaceHolders(RestPath &&restPath, PathReceived &&pathReceived) noexcept;

            PlaceHolders(const RestPath &restPath, PathReceived &&pathReceived) noexcept;
            PlaceHolders(const RestPath restPath, PathReceived pathReceived) noexcept;


            std::vector<std::tuple<std::string,std::string>> getPlaceholders();

            template<typename T, typename P>
            T get(P &&placeholderName) const;

            template<typename T, typename P>
            T getQueryParam(P &&paramName) const;

            template<typename T, typename P>
            std::vector<T> getQueryParams(P &&paramName) const;

        private:
            std::string getInternal(std::string &&) const;

            RestPath restPath;
            PathReceived pathReceived;
        };


        template<typename T, typename F>
        inline T PlaceHolders::get(F &&placeolder) const {
            return boost::lexical_cast<T>(getInternal(std::forward<F>(placeolder)));
        }

        template<typename T, typename P>
        inline T PlaceHolders::getQueryParam(P &&param) const {
            auto queryParams = pathReceived.getQueryParams();
            auto found = queryParams.find(std::forward<P>(param));
            if (found == queryParams.end()) {
                throw QueryParamNotFound{};
            }
            return boost::lexical_cast<T>(found->second.values[0]);
        }


        template<typename T, typename P>
        inline std::vector<T> PlaceHolders::getQueryParams(P &&param) const {
            auto queryParams = pathReceived.getQueryParams();
            auto found = queryParams.find(std::forward<P>(param));
            if (found == queryParams.end()) {
                throw QueryParamNotFound{};
            }
            std::vector<T> result;
            for (auto & value: found->second.values){
                result.push_back(boost::lexical_cast<T>(value));
            }
            return result;
        }


    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_PLACEHOLDERS_H_ */
