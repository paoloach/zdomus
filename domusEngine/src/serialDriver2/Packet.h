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
#include <boost/log/trivial.hpp>
#include <zigbee/ExtAddress.h>

namespace zigbee {
    class Packet {
    public:
        Packet(){}
        Packet(Packet && packet):data(std::move(packet.data)),size_(packet.size_){}
        using iterator = uint8_t  *;
        void resize(uint32_t size){
            data = std::make_unique<uint8_t []>(size+4);
            this->size_ = size;}
        iterator begin() {return data.get();}
        iterator end() {return data.get()+size_;}
        uint32_t size() {return size_;}

        uint8_t getCmdCode(){return data[0];}
        uint8_t operator[](uint32_t index){return data[index];}

        uint8_t getUint8(uint32_t index){
            if (index > size_){
                BOOST_LOG_TRIVIAL(error) << "Index out of bound: index: " << index << " but only " << size_ << " bytes";
                return 0;
            } else
                return data[index];
        }
        ExtAddress getExtAddress(uint32_t index){
            if(index > size_-8){
                BOOST_LOG_TRIVIAL(error) << "Index out of bound: requested range: " << index  << "-" << (index+8)<< " but only " << size_ << " bytes";
                return 0;
            }

            return ExtAddress(data.get() + index);
        }

        uint16_t getUint16(uint32_t index){
            if(index > size_-1){
                BOOST_LOG_TRIVIAL(error) << "Index out of bound: indexes: " << index  << "," << (index+1)<< " but only " << size_ << " bytes";
                return 0;
            }
            return *(boost::endian::little_to_native((uint16_t *) &data[index]));
        }
        friend std::ostream &operator<<(std::ostream & out, const Packet & packet){
            out << "{ ";
            for(uint8_t * b = packet.data.get(); b != packet.data.get() + packet.size_; b++){
                out << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)(*b) << " ";
            }
            out << "}";
            return out;
        }
    private:
        std::unique_ptr<uint8_t[]> data;
        size_t size_;
    };
}

#endif //DOMUS_ENGINE_PACKET_H
