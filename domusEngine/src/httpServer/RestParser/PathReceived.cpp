/*
 * PathReceived.cpp

 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */
#include<boost/tokenizer.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/filesystem/path.hpp>
#include "PathReceived.h"

using std::string;

namespace zigbee {
    namespace http {

        PathReceived::PathReceived(string &&uri) noexcept {
            init(std::move(uri));
        }

        void PathReceived::init(std::string &&uri) noexcept {
            using Separator=boost::char_separator<char>;
            using Tokenizer=boost::tokenizer<Separator>;
            auto queryDelim = uri.find('?');

            if (queryDelim == std::string::npos) {
                createElements(std::move(uri));
            } else {
                createElements(uri.substr(0, queryDelim));
                auto queryString = uri.substr(queryDelim + 1);
                Separator separator("&");
                Tokenizer tokens(queryString, separator);
                for (string token: tokens) {
                    RestQuery restQuery(std::move(token));
                    queryParams.insert({restQuery.name, restQuery});
                }

            }
        }


        void PathReceived::createElements(std::string &&uri) {
            boost::filesystem::path path(uri);
            for (const auto &element : path) {
                if (element != "/" && element != R"(\)")
                    elements.push_back(element.string());
            }

        }

        bool operator==(const zigbee::http::PathReceived &a, const zigbee::http::PathReceived &b) {

            if (a.elements != b.elements)
                return false;
            return a.queryParams == b.queryParams;

        }

        bool operator<(const zigbee::http::PathReceived &a, const zigbee::http::PathReceived &b) {

            if (a.elements != b.elements)
                return a.elements < b.elements;
            return a.queryParams < b.queryParams;
        }

        PathReceived::operator std::string() const {
            std::string result;

            for (auto &element: elements) {
                result += "/" + element;
            }

            if (queryParams.empty()) {
                std::vector<std::string> params;
                for (auto &param: queryParams) {
                    params.push_back(param.first + "=" + static_cast<std::string>(param.second));
                }
                result += string("?") + boost::algorithm::join(params, "&");
            }
            return result;
        }


    } // end namespace http
} /* namespace zigbee */

