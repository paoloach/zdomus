//
// Created by paolo on 19/09/16.
//

#ifndef DOMUS_ENGINE_DEVICEINFODISPATCHER_H
#define DOMUS_ENGINE_DEVICEINFODISPATCHER_H

#include <set>
#include <map>
#include <zigbee/NwkAddr.h>
#include <boost/asio/detail/shared_ptr.hpp>
#include <zigbee/messageStructure/DeviceInfoMessage.h>


namespace zigbee {
    class DeviceInfoDispatcher {
    public:
        class DeviceInfoObserver {
        public:
            virtual void newDeviceInfo(DeviceInfoMessage *)=0;
        };

        void add(DeviceInfoObserver * observer, NwkAddr address);
        void remove(DeviceInfoObserver * observer, NwkAddr address);
        void dispatch(DeviceInfoMessage *);
    private:
        std::map<NwkAddr, std::set< DeviceInfoObserver * >> observers;
    };

}


#endif //DOMUS_ENGINE_DEVICEINFODISPATCHER_H
