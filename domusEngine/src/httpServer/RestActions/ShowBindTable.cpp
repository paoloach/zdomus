//
// Created by paolo on 03/04/16.
//
#include <thread>

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
                                   Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response) {

        Value root(arrayValue);
        auto & bindTable = singletons.getBindTable();
        for (auto &entry: bindTable.getEntries()) {
            Value jsonEntry(objectValue);
            jsonEntry["sourceAddr"] = Value(std::get<0>(entry).address.getId());
            jsonEntry["sourceEndPoint"] = Value(std::get<0>(entry).endpoint.getId());
            jsonEntry["cluster"] = Value(std::get<1>(entry).getId());
            jsonEntry["destAddr"] = Value(std::get<2>(entry).address.getId());
            jsonEntry["destEndpoint"] = Value(std::get<2>(entry).endpoint.getId());
            root.append(jsonEntry);
        }

        response.send() << root;

    }

  }
}

