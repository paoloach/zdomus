//
// Created by paolo on 23/05/17.
//

#include <boost/log/trivial.hpp>
#include <boost/tokenizer.hpp>
#include <zcl/Cluster.h>
#include <zigbee/PowerNodeData.h>
#include <zigbee/messageStructure/ActiveEPErrorMessage.h>
#include "PowerNodeResponseError.h"
#include "../Utils/SingletonObjectsImpl.h"

using std::stoi;

void zigbee::PowerNodeResponseError::operator()(const std::string &msg) {
    boost::char_separator<char> sep(", ");
    boost::tokenizer<boost::char_separator<char> > tok(msg, sep);
    try {
        auto powerNodeData = std::make_shared<PowerNodeData>();
        auto tokIter = tok.begin();
        tokIter++;
        powerNodeData->nwkAddr = NwkAddr{stoi(*tokIter, nullptr, 16)};
        tokIter++;
        auto status = stoi(*tokIter, nullptr, 16);
        BOOST_LOG_TRIVIAL(error) <<"error requesting power node for device " << std::hex << powerNodeData->nwkAddr << " because " << errorCodeToString(status);
        powerNodeData->error=true;

        singletons.getZigbeeDevice()->setPowerNode( powerNodeData);
    } catch (boost::bad_lexical_cast &e) {
        BOOST_LOG_TRIVIAL(error) << "Unable to parse the message: " << e.what();
    }

}
