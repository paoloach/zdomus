//
// Created by paolo on 04/01/18.
//

#ifndef ZIGBEE_LIB_NO_VECTOR_UINT8_EXCEPTION_H
#define ZIGBEE_LIB_NO_VECTOR_UINT8_EXCEPTION_H

#include <exception>
#include <any>
#include <sstream>

namespace zigbee {
    class NoVectorUInt8Exception : public std::exception {
    public:
        std::any value;

        NoVectorUInt8Exception(std::any &any) : value(any) {
        }

        const char *what() const noexcept override {
            std::stringstream stream;

            stream << "The type " << value.type().name() << " is not of type vector uint8_t";
        }

    };
}


#endif //ZIGBEE_LIB_NOBOOLEXCEPTION_H
