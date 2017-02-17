//
// Created by paolo on 16/05/16.
//

#ifndef DOMUS_ENGINE_RESTQUERY_H
#define DOMUS_ENGINE_RESTQUERY_H

#include <string>
#include <vector>
#include <tuple>

namespace zigbee {
    namespace http {
        class RestQuery {
        public:
            RestQuery() {};

            RestQuery(std::string &&queryString);

        public:
            std::string name;
            std::vector<std::string> values;

            operator std::string() const ;


            friend bool operator==(const RestQuery &a, const RestQuery &b);
            friend bool operator<(const RestQuery &a, const RestQuery &b);
        };
    }
}


#endif //DOMUS_ENGINE_RESTQUERY_H
