//
// Created by paolo on 24/06/16.
//

#include <zcl/ZCLAttribute.h>
#include <zigbee/ZigbeeDevice.h>
#include <set>
#include "AttributeWriter.h"

namespace zigbee {

    AttributeWriterResult AttributeWriter::write(NwkAddr nwkAddr, EndpointID endpointID, Cluster * cluster, Json::Value value) {
        AttributeWriterResult results;
        auto attributes = value["attributes"];
        if (!attributes.isArray()) {
            return results;
        }
        for (Json::Value::ArrayIndex i = 0; i < attributes.size(); i++) {
            auto attribute = attributes[i];
            addElement(nwkAddr, endpointID, cluster, std::move(attribute), results);
        }
        return results;
    }

    void AttributeWriter::addElement(NwkAddr nwkAddr, EndpointID endpointID, zigbee::Cluster *cluster, Json::Value &&value,
                                     AttributeWriterResult &results) {
        auto jsonId = value["id"];
        if (!jsonId.isInt()) {
            return;
        }
        int id = jsonId.asInt();
        auto jsonType = value["type"];
        if (!jsonType.isString()) {
            return;
        }
        auto jsonData = value["data"];
        auto type = jsonType.asString();
        auto zigbeeDevice = singletons->getZigbeeDevice();
        auto attribute = cluster->getAttribute(id);
        auto &rawValue = attribute->getAttributeRawValue();
        if (type == "string") {
            if (!jsonData.isString()) {
                return;
            }
            rawValue(jsonData.asString());
        } else  if (type == "int" && jsonData.isInt64()){
            rawValue(jsonData.asInt64());
        } else  if (type == "raw" && jsonData.isArray()){
            std::vector<uint8_t > rawData;
            for (Json::Value::ArrayIndex i = 0; i < jsonData.size(); i++) {
                rawData.push_back(jsonData[i].asInt());
            }

            rawValue(rawData);
        } else {
            return;
        }
        zigbeeDevice->writeAttribute(nwkAddr, endpointID, cluster->getId(), id, rawValue.type, rawValue.rawData.size(), &rawValue.rawData[0]);
        results.add(id);
    }
}




