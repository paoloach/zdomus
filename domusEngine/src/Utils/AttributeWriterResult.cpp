//
// Created by paolo on 12/07/16.
//

#include "AttributeWriterResult.h"
#include "../json/json/json.h"
#include <sstream>

std::string AttributeWriterResult::toJSon() {
    Json::Value root{Json::ValueType::objectValue};
    Json::Value data(Json::ValueType::arrayValue);
    uint index = 0;
    for (int id: ids){
        data[index] = id;
        index++;
    }
    root["attributes"] = data;
    std::stringstream stream;

    stream << root;

    return stream.str();
}

