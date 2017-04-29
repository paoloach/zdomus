#include <boost/spirit/include/karma.hpp>

#include "ZigbeeTypes.h"

std::ostream &operator<<(std::ostream &out, const ZigbeeAttributeIds &attributeIds) {
    boost::spirit::karma::generate(
            std::ostream_iterator<char>{out},                           // destination: output iterator
            boost::spirit::karma::int_ % ',',                   // the generator
            attributeIds                               // the data to output
    );
    return out;
}

std::istream &operator>>(std::istream &in, ZigbeeAttributeIds &attributeIds) {
    ZigbeeAttributeId id;
    while (true) {
        in >> std::hex >> id >> std::dec;
        if (in.fail()) {
            break;
        }
        attributeIds.push_back(id);
        if (in.peek() != ',')
            break;
        in.get();
    }
    return in;
}