/*
 * ZDevice.cpp
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>

#include "ZDevice.h"
#include "Exceptions/InvalidZEndpointException.h"

namespace zigbee {

    ZDevice::ZDevice() {
        capabilities = 0;
    }

    ZDevice::ZDevice(const AnnunceMessage &message) : nwkAddr(message.nwkAddr) {
        capabilities = message.capabilities;
        extAddr = message.extAddr;
    }

    ZDevice::ZDevice(const ExtAddress &extAddress, NwkAddr nwkAddress, uint8_t deviceCapabilities,
                     std::initializer_list<ZEndpoint> listEndpoint) :
            extAddr(extAddress), nwkAddr{nwkAddress}, capabilities{deviceCapabilities} {
        for (const ZEndpoint &zEndpoint: listEndpoint) {
            endpoints.insert({zEndpoint.getEndpoint(), zEndpoint});
        }
    }


    ZDevice::ZDevice(const ExtAddress &extAddr, NwkAddr nwkAddr, std::set<NwkAddr> children) : extAddr(extAddr),
                                                                                               nwkAddr(nwkAddr),
                                                                                               capabilities(0),
                                                                                               children(children) {

    }


    ZDevice::~ZDevice() {
    }

    bool ZDevice::put(const SimpleDescMessage &simpleDescMsg) {
        ZEndpoint endpoint(simpleDescMsg);
        EndpointID endpoindId(simpleDescMsg.endpoint);
        if (endpoints.count(endpoindId)) {
            if (endpoints[endpoindId] == endpoint) {
                return false;
            } else {
                endpoints[endpoindId] = endpoint;
                return true;
            }
        } else {
            endpoints[endpoindId] = endpoint;
            return true;
        }
    }


    ZEndpoint ZDevice::getEndpoint(EndpointID endpointId) const {
        auto found = endpoints.find(endpointId);
        if (found == endpoints.end()) {
            throw InvalidZEndpointException(nwkAddr, endpointId);
        } else {
            return found->second;
        }
    }


    bool ZDevice::isEndpointPresents(EndpointID endpointId) const {
        return endpoints.count(endpointId) > 0;
    }


} /* namespace zigbee */

