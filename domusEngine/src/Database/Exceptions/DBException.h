/*
 * DBException.h
 *
 *  Created on: 23/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_DATABASE_EXCEPTIONS_DBEXCEPTION_H_
#define SRC_DATABASE_EXCEPTIONS_DBEXCEPTION_H_

#include <exception>
#include <string>

namespace zigbee {

    class DBException : public std::exception {
    public:
        DBException() = default;

        DBException(const std::string &message) : message(message) {
        }

        virtual ~DBException() noexcept = default;

        virtual const char *what() const noexcept {
            return message.c_str();
        }

    protected:
        std::string message;
    };

} /* namespace zigbee */

#endif /* SRC_DATABASE_EXCEPTIONS_DBEXCEPTION_H_ */
