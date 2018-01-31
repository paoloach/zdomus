/*
 * AttributeNotFoundException.h
 *
 *  Created on: 15/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_EXCEPTIONS_NO_INT32_EXCEPTION_H_
#define SRC_ZCL_EXCEPTIONS_NO_INT32_EXCEPTION_H_

#include <exception>

namespace zigbee {

    class NoInt32Exception : std::exception {
    public:
        std::any value;

        NoInt32Exception(std::any &any) : value(any) {
        }

        const char *what() const noexcept override {
            std::stringstream stream;

            stream << "The type " << value.type().name() << " is not of type int32_t";
            return  stream.str().c_str();
        }


        virtual ~NoInt32Exception() noexcept = default;;
    };

} /* namespace zigbee */

#endif /* SRC_ZCL_EXCEPTIONS_ATTRIBUTENOTFOUNDEXCEPTION_H_ */
