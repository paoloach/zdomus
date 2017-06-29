//
// Created by paolo on 08/06/17.
//
#include <boost/spirit/include/karma.hpp>
#include "AttributesKey.h"

namespace zigbee {
    bool AttributesKey::operator==(const AttributesKey &other) const {
        return networkAddress == other.networkAddress && endpoint == other.endpoint && clusterId == other.clusterId &&
               attributesId == other.attributesId;
    }

    bool AttributesKey::operator<(const AttributesKey &other) const {
        if (networkAddress == other.networkAddress) {
            if (endpoint == other.endpoint) {
                if (clusterId == other.clusterId) {
                    return attributesId < other.attributesId;
                } else {
                    return clusterId < other.clusterId;
                }
            } else {
                return endpoint < other.endpoint;
            }
        } else {
            return networkAddress < other.networkAddress;
        }
    }

    std::ostream &operator<<(std::ostream &out, const AttributesKey &key) {
        out << "{" << key.networkAddress << "," << key.endpoint << "," << key.clusterId << ",";
        boost::spirit::karma::generate(
                std::ostream_iterator<char>{out},                           // destination: output iterator
                boost::spirit::karma::int_ % ',',                   // the generator
                key.attributesId                               // the data to output
        );
        out << "}";
        return out;
    }
}