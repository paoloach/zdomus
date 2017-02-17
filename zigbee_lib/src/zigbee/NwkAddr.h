/*
 * NwkAddr.h
 *
 *  Created on: 11/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_NWKADDR_H_
#define SRC_ZIGBEE_NWKADDR_H_

#include <string>
#include <boost/lexical_cast.hpp>
#include <ostream>
#include <istream>
#include <iomanip>
#include <zigbee/ZigbeeTypes.h>

namespace zigbee {

    class NwkAddr {
    public:
        constexpr NwkAddr() :
                address(0) {
        }

        explicit constexpr NwkAddr(int address) :
                address(address) {
        }

        explicit NwkAddr(const std::string &addressSrc) :
                address(std::stoul(addressSrc, 0, 16)){
        }

        constexpr NwkAddr(const NwkAddr &other) = default;

        bool operator==(const NwkAddr other) const {
            return address == other.address;
        }

        bool operator==(int other) const {
            return address == other;
        }

        bool operator<(const NwkAddr other) const {
            return address < other.address;
        }

        bool operator<(int other) const {
            return address < other;
        }

        ZigbeeNwkAddress getId() const {
            return address;
        }

        void setId(int id) {
            address = id;
        }

        friend std::ostream &operator<<(std::ostream &out, const NwkAddr &address);

        friend std::istream &operator>>(std::istream &in, NwkAddr &address);

    private:
        int address;
    };

    inline std::ostream &operator<<(std::ostream &out, const NwkAddr &address) {
        out << std::hex << std::uppercase << std::setfill('0') << std::setw(4) << address.address << std::dec;
        return out;
    }

    inline std::istream &operator>>(std::istream &in, NwkAddr &address) {
        in >> std::hex >> address.address >> std::dec;
        return in;
    }

} /* namespace zigbee */

#endif /* SRC_ZIGBEE_NWKADDR_H_ */
