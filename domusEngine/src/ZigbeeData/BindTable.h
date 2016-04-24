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
#include <zigbee/ClusterID.h>

#include "../usb/BindResponse.h"
#include "ZElement.h"

namespace zigbee {


    class BindTable {
    public:
        void add(BindResponse && response );

        auto getEntries() const {return entries;}
    private:
        std::vector<std::tuple<ZElement, ClusterID, ZElement>> entries;
    };

}

#endif //DOMUS_ENGINE_BINDTABLE_H
