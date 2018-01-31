//
// Created by paolo on 30/01/18.
//
#include <exception>
#include <sstream>

#ifndef ZIGBEE_LIB_NOVALIDLOGICALTYPEEXCEPTION_H
#define ZIGBEE_LIB_NOVALIDLOGICALTYPEEXCEPTION_H
namespace zigbee {
    class NoValidLogicalTypeException : std::exception {
    private:
        uint value;
    public:
        NoValidLogicalTypeException(uint value):value(value){

        }

        const char *what() const noexcept override {
            std::stringstream stream;

            stream << "The value  " << value << " is not a valid LogicType";
            return  stream.str().c_str();
        }

        virtual ~NoValidLogicalTypeException() noexcept = default;
    };
}

#endif //ZIGBEE_LIB_NOVALIDLOGICALTYPEEXCEPTION_H
