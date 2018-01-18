//
// Created by paolo on 23/12/17.
//

#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/string_literal.hpp>
#include <zigbee/ZigbeeDevice.h>
#include <zigbee/ExtAddress.h>
#include "AnnunceSerial2Executor.h"
#include "../ZigbeeData/ZDevices.h"

namespace zigbee {
    void AnnunceSerial2Executor::operator()(Packet &&packet)  {
        BOOST_LOG_NAMED_SCOPE("Annunce device");
        AnnunceMessage annunceMessage;
        annunceMessage.nwkAddr = packet.getUint16(1);
        std::copy(packet.begin()+3, packet.begin()+11, annunceMessage.extAddr);

        BOOST_LOG_TRIVIAL(info) << "Annunce device " << NwkAddr{annunceMessage.nwkAddr} << " - " << ExtAddress(annunceMessage.extAddr);
        annunceMessage.capabilities = packet.getUint8(11);
        singletons->getZDevices()->put(annunceMessage);

        NwkAddr nwkAddr{annunceMessage.nwkAddr};
        BOOST_LOG_TRIVIAL(info) << "Request endopoint";
        singletons->getZigbeeDevice()->requestActiveEndpoints(nwkAddr);
        //sleep(1);
        //BOOST_LOG_TRIVIAL(info) << "Request bind table";
        //singletons.getZigbeeDevice()->requestBindTable(nwkAddr);
    }
}

