/*
 * PathElement.h
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_PATHELEMENT_H_
#define SRC_HTTPSERVER_RESTPARSER_PATHELEMENT_H_

#include <string>
#include <iostream>

namespace zigbee {
    namespace http {

        class PathElement {
        public:
            PathElement(const std::string &value) noexcept;

        public:
            std::string getValue() const noexcept { return value; }

            bool isPlaceholder() const noexcept { return placeholder; }

            bool operator==(const PathElement &other) const noexcept { return value == other.value && placeholder == other.placeholder; }

        private:
            std::string value;
            bool placeholder;
        };

        inline std::ostream & operator<<(std::ostream & out, const PathElement pathElement) {
            if (pathElement.isPlaceholder()){
                out<< "{" << pathElement.getValue() << "}";
            } else {
                out << pathElement.getValue();
            }
            return out;
        }

    } /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_PATHELEMENT_H_ */
