//
// Created by paolo on 16/05/16.
//

#include <boost/tokenizer.hpp>
#include "RestQuery.h"

using boost::tokenizer;
using boost::char_separator;
using std::string;
zigbee::http::RestQuery::RestQuery(std::string &&queryString) {

    auto ugualPos = queryString.find_first_of('=');
    if (ugualPos == string::npos){
        name = queryString;
    } else {
        name = queryString.substr(0,ugualPos);
        char_separator<char> sep(",");
        tokenizer<boost::char_separator<char>> tokens(queryString.substr(ugualPos+1),sep);
        for (const auto & token: tokens){
            values.push_back(std::move(token));
        }
    }

}

