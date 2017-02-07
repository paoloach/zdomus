/*
 * RestValue.h
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTVALUE_H_
#define SRC_HTTPSERVER_RESTVALUE_H_

#include <boost/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <string>
#include <utility>

namespace zigbee {
    namespace http {

        class RestValue {
        public:
            RestValue(const std::string &path, std::string value) : path(path), value(std::move(value)) {}

            virtual ~RestValue();

            const boost::filesystem::path &getPath() const {
                return path;
            }

            const std::string &getValue() const {
                return value;
            }

            template<typename t>
            void set(const boost::filesystem::path &path, t value) {
                this->path = path;
                this->value = boost::lexical_cast<std::string>(value);
            }


        private:
            boost::filesystem::path path;
            std::string value;
        };

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTVALUE_H_ */
