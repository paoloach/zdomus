//
// Created by paolo on 03/04/16.
//

#include "BindTablePT.h"

using boost::property_tree::ptree;

zigbee::http::BindTablePT::BindTablePT(zigbee::BindTable &bindTable) noexcept {
    ptree entryPT;
    for (auto &entry: bindTable.getEntries()) {
        ptree entryPT;
        entryPT.add("sourceAddr", std::get<0>(entry).address);
        entryPT.add("sourceEndPoint", std::get<0>(entry).endpoint);
        entryPT.add("cluster", std::get<1>(entry));
        entryPT.add("destAddr", std::get<2>(entry).address);
        entryPT.add("destEndpoint", std::get<2>(entry).endpoint);
        push_back({"entry", entryPT});
    }
}

