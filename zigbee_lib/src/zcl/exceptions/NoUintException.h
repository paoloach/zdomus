/*
 * AttributeNotFoundException.h
 *
 *  Created on: 15/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZCL_EXCEPTIONS_NO_UINT_EXCEPTION_H_
#define SRC_ZCL_EXCEPTIONS_NO_UINT_EXCEPTION_H_

#include <exception>
#include <any>
#include <sstream>

namespace zigbee {

    class NoUintException : std::exception {
    public:
        std::any value;

        NoUintException(std::any &any) : value(any) {
        }

        const char *what() const noexcept override {
            std::stringstream stream;

            stream << "The type " << value.type().name() << " is not of type uint32_t";
        }


        virtual ~NoUintException() noexcept = default;;
    };

} /* namespace zigbee */

#endif /* SRC_ZCL_EXCEPTIONS_ATTRIBUTENOTFOUNDEXCEPTION_H_ */
