//
// Created by paolo on 02/04/16.
//

#ifndef DOMUS_ENGINE_BINDTABLE_H
#define DOMUS_ENGINE_BINDTABLE_H

#include <inttypes.h>
#include <set>
#include <zigbee/messageStructure/ZAddrType.h>
#include <zigbee/messageStructure/BindTableResponseMessage.h>
#include <memory>

#include "ExtAddress.h"

namespace zigbee {

    class BindTable {
    public:
        void add(std::shared_ptr<BindTableResponseMessage>);

        auto getEntries() const {return entries;}
    private:
        std::set<std::tuple<ExtAddress, int, uint, uint, int>> entries;
    };

}

#endif //DOMUS_ENGINE_BINDTABLE_H
