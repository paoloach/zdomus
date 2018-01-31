//
// Created by paolo on 25/12/17.
//

#ifndef DOMUS_ENGINE_PACKETSEND_H
#define DOMUS_ENGINE_PACKETSEND_H

#include <ostream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <zigbee/NwkAddr.h>
#include <zigbee/EndpointID.h>
#include <zigbee/ClusterID.h>
#include <zcl/ZCLDataType.h>
#include <zigbee/ExtAddress.h>

namespace zigbee {
    class PacketSend {
    public:
        PacketSend(){}
        PacketSend(PacketSend && other):data(std::move(other.data)){};
        uint32_t size(){return data.size();}
        uint8_t * begin() {return &data[0];}
        void push(NwkAddr nwkAddr){push(nwkAddr.getId());}
        void push(EndpointID endpointID){push(endpointID.getId());}
        void push(ClusterID clusterID){push(clusterID.getId());}
        void push(ZCLTypeDataType dataType){push(static_cast<uint8_t >(dataType));}
        void push(ExtAddress && extAddress){
            auto iter = extAddress.asArray();
            for(int i=0; i < 8; i++){
                push(*iter);
                iter++;
            }
        }
        void push(uint16_t value){
            data.push_back(value );
            data.push_back(value >> 8);
        }
        void push(uint8_t value){
            data.push_back(value );
        }

        inline friend std::ostream & operator <<(std::ostream & out, const PacketSend & packet){
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


#endif //DOMUS_ENGINE_PACKETSEND_H
