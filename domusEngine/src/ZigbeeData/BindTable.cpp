//
// Created by paolo on 02/04/16.
//

#include <boost/log/trivial.hpp>
#include "BindTable.h"


namespace zigbee {

    void BindTable::add(BindResponse && response ) {
        BOOST_LOG_TRIVIAL(info) << "new bind entry";
        entries.push_back(std::make_tuple<ZElement, ClusterID, ZElement>(ZElement(response.srcAddr,response.srcEP), std::move(response.clusterId), ZElement(response.dstAddr,response.dstEP)));
    }

}

