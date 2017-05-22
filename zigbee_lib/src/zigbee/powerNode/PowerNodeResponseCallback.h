//
// Created by paolo on 22/05/17.
//

#ifndef ZIGBEE_LIB_POWERNODERESPONSECALLBACK_H
#define ZIGBEE_LIB_POWERNODERESPONSECALLBACK_H

#include <memory>


namespace zigbee {
    class PowerNodeData;
    class PowerNodeResponseCallback {
    public:
        virtual ~PowerNodeResponseCallback() = default;

        virtual void response(std::shared_ptr<PowerNodeData> powerNode)=0;
        virtual void timeout()=0;
    };
}

#endif //ZIGBEE_LIB_POWERNODERESPONSECALLBACK_H
