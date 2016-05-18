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