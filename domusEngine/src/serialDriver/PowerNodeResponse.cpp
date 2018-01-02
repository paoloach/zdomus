//
// Created by paolo on 11/05/17.
//

#include "../Utils/SingletonObjectsImpl.h"
#include "PowerNodeResponse.h"

#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <zcl/Cluster.h>
#include <zigbee/PowerNodeData.h>

using std::stoi;

namespace zigbee {

    void PowerNodeResponse::operator()(const std::string &msg) {
        boost::char_separator<char> sep(", ");
        boost::tokenizer<boost::char_separator<char> > tok(msg, sep);
        try {
            auto powerNodeData = std::make_shared<PowerNodeData>();
            auto tokIter = tok.begin();
            tokIter++;
            powerNodeData->nwkAddr = NwkAddr{stoi(*tokIter, nullptr, 16)};
            tokIter++;

            powerNodeData->powerMode = powerModefrom(stoi(*tokIter, nullptr, 16));
            tokIter++;
            powerNodeData->availablePowerSource = PowerSource(stoi(*tokIter, nullptr, 16));
            tokIter++;
            powerNodeData->currentPowerSource = PowerSource(stoi(*tokIter, nullptr, 16));
            tokIter++;
            powerNodeData->currentPowerSourceLevel = powerLevelFrom(stoi(*tokIter, nullptr, 16));

            singletons.getZigbeeDevice()->setPowerNode( powerNodeData);
        } catch (boost::bad_lexical_cast &e) {
            BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
        }
    }
}