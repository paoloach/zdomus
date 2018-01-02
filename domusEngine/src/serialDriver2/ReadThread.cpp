//
// Created by paolo on 20/12/17.
//
#include <boost/log/trivial.hpp>
#include <boost/fiber/algo/round_robin.hpp>
#include <boost/fiber/operations.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include "ReadThread.h"
#include "Serial2ResponseExecutor.h"
#include "Packet.h"

namespace zigbee {
    static const boost::log::string_literal LOG_SCOPE("serial driver");
    constexpr uint8_t HEADER1 = 0x55;
    constexpr uint8_t HEADER2 = 0xAA;
    constexpr uint8_t HEADER3 = 0x42;

    enum class Status {
        Header1,
        Header2,
        Header3,
        Size,
        Data
    };

    void readThread(SingletonObjectsImpl & singletonObjects, int serialFd) {
        Status  status  =  Status::Header1;
        Serial2ResponseExecutor responseExecutor(singletonObjects);
        int n;
        fd_set readFd;
        struct timeval timeout;
        std::this_thread::__sleep_for(1s, 0us);
        BOOST_LOG_NAMED_SCOPE(LOG_SCOPE);
        uint8_t c;
        while (true) {
            FD_ZERO(&readFd);
            FD_SET(serialFd, &readFd);
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            Packet packet;
            Packet::iterator iter;
            uint   packetSize;
            while (select(serialFd + 1, &readFd, NULL, NULL, &timeout) > 0) {
                n = read(serialFd, &c, 1);
                if (n > 0) {
                    switch (status){
                        case Status::Header1:
                            if (c==HEADER1){
                                status = Status::Header2;
                            }
                            break;
                        case Status::Header2:
                            if (c==HEADER2){
                                status = Status::Header3;
                            } else {
                                BOOST_LOG_TRIVIAL(error) << "Out of sync reading from serial port ";
                                status = Status::Header1;
                            }
                            break;
                        case Status::Header3:
                            if (c==HEADER3){
                                status = Status::Size;
                            } else {
                                status = Status::Header1;
                                BOOST_LOG_TRIVIAL(error) << "Out of sync reading from serial port ";
                            }
                            break;
                        case Status::Size:
                            packetSize = c;
                            packet.resize(packetSize+1);
                            status = Status::Data;
                            iter = packet.begin();
                            break;
                        case Status::Data:
                            *iter = c;
                            iter++;
                            if (iter == packet.end()){
                                status = Status::Header1;
                                responseExecutor.execute(std::move(packet));
                            }
                            break;
                    }
                }
            }

        }

    }

}
