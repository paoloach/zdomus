//
// Created by paolo on 08/06/17.
//

#ifndef ZIGBEE_LIB_ATTRIBUTESRESPONSEQUEUE_H
#define ZIGBEE_LIB_ATTRIBUTESRESPONSEQUEUE_H

#include <queue>
#include <tuple>
#include <boost/fiber/mutex.hpp>
#include <boost/fiber/unbuffered_channel.hpp>
#include <boost/fiber/fiber.hpp>
#include "NwkAddr.h"
#include "ResponseCallback.h"
#include "AttributesResponseCallback.h"
#include "AttributesKey.h"

namespace zigbee {
    class ZigbeeDevice;
    class AttributesResponseQueue {
        class Responses {
        public:
            Responses(std::vector<ZigbeeAttributeId> & attributesId, std::unique_ptr<AttributesResponseCallback> && callback);
            void arrived(ZCLAttribute * attribute, int index);
            void timeout(int index);
        private:
            bool allNotified(){
                return std::find(notified.begin(), notified.end(), false) == notified.end();
            }
            std::vector<bool>  notified;
            std::vector<ZCLAttribute *> attributes;
            std::unique_ptr<AttributesResponseCallback> callback;
        };

        class SingleAttrResponse : public ResponseCallback<ZCLAttribute * > {
        public:
            SingleAttrResponse(int index, std::shared_ptr<Responses> responses): index(index), responses(responses){}
        private:
            void response(ZCLAttribute * attribute) override;
            void timeout() override ;

            int index;
            std::shared_ptr<Responses> responses;
        };

    public:
        AttributesResponseQueue(ZigbeeDevice * zigbeeDevice): zigbeeDevice(zigbeeDevice){}
        void add(AttributesKey, std::unique_ptr<AttributesResponseCallback> && callback);
    private:
        ZigbeeDevice * zigbeeDevice;
    };
}


#endif //ZIGBEE_LIB_ATTRIBUTESRESPONSEQUEUE_H
