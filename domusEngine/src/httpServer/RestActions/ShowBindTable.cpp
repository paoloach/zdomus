//
// Created by paolo on 03/04/16.
//
#include <thread>
#include <boost/log/trivial.hpp>

#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "ShowBindTable.h"
#include "../../json/json/json.h"

#include "../MediaTypeProducerFactory.h"
#include "../../Utils/SingletonObjects.h"

using namespace Json;

namespace zigbee {

    namespace http {
        void ShowBindTable::operator()(const zigbee::http::PlaceHolders &&,
                                       ServerRequest &request,
                                       Poco::Net::HTTPServerResponse &response) {
            response.setContentType(Poco::Net::MediaType("application", "json"));
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
            BOOST_LOG_TRIVIAL(info) << "request BindTable: " << request.getContentType();
            Value root(arrayValue);
            auto &bindTable = singletons.getBindTable();
            for (auto &entry: bindTable.getEntries()) {
                Value jsonEntry(objectValue);
                jsonEntry["sourceAddr"] = Value(std::get<0>(entry).address.getId());
                jsonEntry["sourceEndpoint"] = Value(std::get<0>(entry).endpoint.getId());
                jsonEntry["cluster"] = Value(std::get<1>(entry).getId());
                jsonEntry["destAddr"] = Value(std::get<2>(entry).address.getId());
                jsonEntry["destEndpoint"] = Value(std::get<2>(entry).endpoint.getId());
                root.append(jsonEntry);
            }

            std::ostream &stream = response.send();
            stream << root << "\n";
        }

    }
}

