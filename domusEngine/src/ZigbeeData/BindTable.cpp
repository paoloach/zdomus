//
// Created by paolo on 02/04/16.
//

#include <boost/log/trivial.hpp>
#include "BindTable.h"


namespace zigbee {

    void BindTable::add(std::shared_ptr<BindTableResponseMessage> entry) {
        BOOST_LOG_TRIVIAL(info) << "new bind entry";
        entries.emplace(ExtAddress(entry->srcAddr), entry->srcEP, (uint) (entry->clusterID), (uint) (entry->dstAddr),
                        entry->dstEP);
    }

}

