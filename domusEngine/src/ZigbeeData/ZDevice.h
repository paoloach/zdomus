/*
 * ZDevice.h
 *
 *  Created on: 28/nov/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEEDATA_ZDEVICE_H_
#define SRC_ZIGBEEDATA_ZDEVICE_H_

#include <array>
#include <map>
#include <initializer_list>
#include <zigbee/messageStructure/AnnunceMessage.h>
#include <zigbee/messageStructure/SimpleDescMessage.h>
#include <zigbee/NwkAddr.h>
#include <set>

#include "ZEndpoint.h"
#include "ExtAddress.h"


namespace zigbee {

    class ZDevice {
    public:
        ZDevice();

        ZDevice(const AnnunceMessage &message);

        ZDevice(const ExtAddress &extAddr, NwkAddr nwkAddr, uint8_t capabilities,
                std::initializer_list<ZEndpoint> listEndpoint);

        ZDevice(const ExtAddress &extAddr, NwkAddr nwkAddr, std::set<NwkAddr> children);

        virtual ~ZDevice()=default;

    public:
        bool put(const SimpleDescMessage &simpleDescMsg);

        ZEndpoint getEndpoint(EndpointID endpointId) const;

        bool isEndpointPresents(EndpointID endpointId) const;

        bool isPan() const {
            return capabilities & 0x01;
        }

        bool isFullFunctionDevice() const {
            return capabilities & 0x02;
        }

        bool isMainPower() const {
            return capabilities & 0x04;
        }

        bool isDisabledRFOnIdle() const {
            return capabilities & 0x08;
        }

        bool isSecure() const {
            return capabilities & 0x40;
        }

        uint8_t getCapabilities() const {
            return capabilities;
        }

        const std::map<EndpointID, ZEndpoint> &getEndpoints() const {
            return endpoints;
        }

        ExtAddress getExtAddr() const {
            return extAddr;
        }

        NwkAddr getNwkAddr() const {
            return nwkAddr;
        }

        std::set<NwkAddr> getChildren() {
                return children;
        };


    private:
        ExtAddress extAddr;
        NwkAddr nwkAddr;
        uint8_t capabilities;
        std::map<EndpointID, ZEndpoint> endpoints;
        std::set<NwkAddr> children;
    };

} /* namespace zigbee */

#endif /* SRC_ZIGBEEDATA_ZDEVICE_H_ */
