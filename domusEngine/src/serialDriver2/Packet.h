//
// Created by paolo on 22/12/17.
//

#ifndef DOMUS_ENGINE_PACKET_H
#define DOMUS_ENGINE_PACKET_H

#include <ostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <boost/endian/conversion.hpp>
#include <zigbee/ExtAddress.h>

namespace zigbee {
    class Packet {
    public:
        Packet(){}
        Packet(Packet && packet):data(std::move(packet.data)){}
        using iterator = std::vector<uint8_t >::iterator;
        void resize(uint32_t size){data.resize(size);}
        iterator begin() {return data.begin();}
        iterator end() {return data.end();}
        uint32_t size() {return data.size();}

        uint8_t getCmdCode(){return data[0];}
        uint8_t operator[](uint32_t index){return data[index];}

        uint8_t getUint8(uint32_t index){
            return data[index];
        }
        ExtAddress getExtAddress(uint32_t index){
            return ExtAddress(data.begin() + index);
        }

        uint16_t getUint16(uint32_t index){
            return *(boost::endian::little_to_native((uint16_t *) &data[index]));
        }
        friend std::ostream &operator<<(std::ostream & out, const Packet & packet){
            out << "{ ";
            for (uint8_t b: packet.data){
                out << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)b << " ";
            }
            out << "}";
            return out;
        }
    private:
        std::vector<uint8_t> data;
    };
}

#endif //DOMUS_ENGINE_PACKET_H
