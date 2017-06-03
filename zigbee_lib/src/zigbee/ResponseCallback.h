//
// Created by paolo on 01/06/17.
//

#ifndef ZIGBEE_LIB_RESPONSECALLBACK_H
#define ZIGBEE_LIB_RESPONSECALLBACK_H

namespace zigbee {
    template <typename  T>
    class ResponseCallback {
    public:
        virtual ~ResponseCallback() = default;

        virtual void response(T ){};
        virtual void timeout(){};
    };
}


#endif //ZIGBEE_LIB_RESPONSECALLBACK_H
