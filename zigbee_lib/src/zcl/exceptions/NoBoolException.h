//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_NOBOOLEXCEPTION_H
#define ZIGBEE_LIB_NOBOOLEXCEPTION_H

#include <exception>
#include <any>
#include <sstream>

namespace zigbee {
    class NoBoolException: public std::exception {
    public:
        std::any value;
        NoBoolException(std::any & any):value(any){
        }
        const char* what() const noexcept override {
            std::stringstream stream;

            stream << "The type " << value.type().name() << " is not of type bool";
            return  stream.str().c_str();
        }

    };
}


#endif //ZIGBEE_LIB_NOBOOLEXCEPTION_H
