//
// Created by paolo on 06/01/18.
//

#ifndef ZIGBEE_LIB_ZCLATTRIBUTENOTAVAILABLEEXCEPTION_H
#define ZIGBEE_LIB_ZCLATTRIBUTENOTAVAILABLEEXCEPTION_H

#include <exception>
#include <string>
#include "zcl/Cluster.h"

namespace zigbee {

    class ZCLAttributeNotAvailableException : public std::exception {
    public:
        ZCLAttributeNotAvailableException(Cluster *parent, int ){
            std::stringstream stream;
            stream << "try to access to not yet available attribute of cluster " << parent->getClusterName() << ", endpoint " << parent->getEndpoint() <<
                   ", node "
                   << parent->getNetworkAddress();
            message = stream.str();
        }

        const char *what() const _GLIBCXX_USE_NOEXCEPT override {
            return message.c_str();
        }

        virtual std::string getMessage() const _GLIBCXX_USE_NOEXCEPT {
            return message;
        }

    private:
        std::string message;

    };

}


#endif //ZIGBEE_LIB_ZCLATTRIBUTENOTAVAILABLEEXCEPTION_H
