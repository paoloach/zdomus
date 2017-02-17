//
// Created by paolo on 16/05/16.
//

#include <boost/tokenizer.hpp>
#include "RestQuery.h"
#include <boost/algorithm/string/join.hpp>


using boost::tokenizer;
using boost::char_separator;
using std::string;
namespace zigbee {
    namespace  http {
        RestQuery::RestQuery(std::string &&queryString) {

            auto ugualPos = queryString.find_first_of('=');
            if (ugualPos == string::npos) {
                name = queryString;
            } else {
                name = queryString.substr(0, ugualPos);
                char_separator<char> sep(",");
                tokenizer<boost::char_separator<char>> tokens(queryString.substr(ugualPos + 1), sep);
                for (const auto &token: tokens) {
                    values.push_back(token);
                }
            }

        }

        bool operator==(const RestQuery &a, const RestQuery &b) {
            if (a.name != b.name)
                return false;
            return a.values == b.values;
        }

        bool operator<(const RestQuery &a, const RestQuery &b) {
            if (a.name != b.name){
                return  a.name < b.name;
            }
            return a.values < b.values;
        }

        RestQuery::operator std::string() const {
            std::string result = name;
            if (!values.empty()) {
                result += "=" + boost::algorithm::join(values, ", ");
            }
            return result;
        }
    }
}

