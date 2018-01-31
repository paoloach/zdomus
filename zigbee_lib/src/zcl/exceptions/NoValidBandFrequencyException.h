//
// Created by paolo on 30/01/18.
//
#include <exception>
#include <sstream>

#ifndef ZIGBEE_LIB_NOVALIDBANDFREQUENCYEXCEPTION_H
#define ZIGBEE_LIB_NOVALIDBANDFREQUENCYEXCEPTION_H

namespace zigbee {
    class NoValidBandFrequencyException : std::exception {
    private:
        uint value;
    public:
        NoValidBandFrequencyException(uint value) : value(value) {}

        virtual ~NoValidBandFrequencyException() noexcept = default;

        const char *what() const noexcept override {
            std::stringstream stream;

            stream << "The value  " << value << " is not a valid Band Frequency";
            return  stream.str().c_str();
        }
    };
}


#endif //ZIGBEE_LIB_NOVALIDBANDFREQUENCYEXCEPTION_H
