//
// Created by paolo on 07/10/16.
//

#include "USBDevice.h"

using Attribute = zigbee::RequestedAttributes::Attribute;

namespace zigbee {
    static const boost::posix_time::time_duration CHECK_NEW_MESSAGE = boost::posix_time::milliseconds(10);
    static const uint8_t raw_1234_4_0_0[] = {0x00, 0x00, 0x00, 0x20, 0x1};
    static const uint8_t raw_1234_4_0_1[] = {0x01, 0x00, 0x00, 0x20, 0x10};
    static const uint8_t raw_1234_4_0_2[] = {0x02, 0x00, 0x00, 0x20, 0x1};
    static const uint8_t raw_1234_4_0_3[] = {0x03, 0x00, 0x00, 0x20, 0x1};
    static const uint8_t raw_1234_4_0_4[] = {0x04, 0x00, 0x00, 0x42, 0x08, 'a', 'c', 'h', 'd', 'j', 'i', 'a', 'n'};
    // model identifier
    static const uint8_t raw_1234_4_0_5[] = {0x05, 0x00, 0x00, 0x42, 0x07, 's', 'w', 'i', 't', 'c', 'h', '1'};
    static const uint8_t raw_1234_6_0_5[] = {0x05, 0x00, 0x00, 0x42, 12, 'l', 'i', 'g', 'h', 't', ' ', 's', 'w', 'i',
                                             't', 'c', 'h'};
    static const uint8_t raw_1235_7_0_5[] = {0x05, 0x00, 0x00, 0x42, 13, 'o', 'n', '/', 'o', 'f', 'f', ' ', 'o', 'u',
                                             't', 'p', 'u', 't'};
    static const uint8_t raw_1235_11_0_5[] = {0x05, 0x00, 0x00, 0x42, 12, 'o', 'n', '/', 'o', 'f', 'f', ' ', 'l', 'i',
                                              'g', 't', 'h'};


    static const uint8_t raw_1234_4_0_6[] = {0x06, 0x00, 0x00, 0x42, 8, '2', '0', '1', '6', '0', '4', '1', '2'};
    static const uint8_t raw_1234_4_0_7[] = {0x07, 0x00, 0x00, 0x30, 4};

    static const uint8_t raw_1234_4_0_16[] = {0x10, 0x00, 0x00, 0x42, 0};
    static const uint8_t raw_1234_4_0_17[] = {0x11, 0x00, 0x00, 0x30, 0};
    static const uint8_t raw_1234_4_0_18[] = {0x12, 0x00, 0x00, 0x10, 1};
    static const uint8_t raw_1234_4_0_19[] = {0x13, 0x00, 0x00, 0x30, 0};
    static const uint8_t raw_1234_4_0_20[] = {0x14, 0x00, 0x00, 0x30, 1};

    static const uint8_t raw_1235_7_6_0[] = {0x0, 0x00, 0x00, 0x10, 1};
    static const uint8_t raw_1235_11_6_0[] = {0x0, 0x00, 0x00, 0x10, 0};

    static const uint8_t raw_1235_5_1026_0[] = {0x0, 0x00, 0x00, 0x29, 0x34, 8};
    static const uint8_t raw_1232_7_1026_0[] = {0x0, 0x00, 0x00, 0x29, 0x89, 8};

    void DomusEngineUSBDevice::initDemoData() {
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 0)] = raw_1234_4_0_0;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 1)] = raw_1234_4_0_1;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 2)] = raw_1234_4_0_2;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 3)] = raw_1234_4_0_3;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 4)] = raw_1234_4_0_4;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 5)] = raw_1234_6_0_5;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 6)] = raw_1234_4_0_6;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 7)] = raw_1234_4_0_7;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 16)] = raw_1234_4_0_16;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 17)] = raw_1234_4_0_17;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 18)] = raw_1234_4_0_18;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 19)] = raw_1234_4_0_19;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(6), ClusterID(0), 20)] = raw_1234_4_0_20;

        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 0)] = raw_1234_4_0_0;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 1)] = raw_1234_4_0_1;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 2)] = raw_1234_4_0_2;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 3)] = raw_1234_4_0_3;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 4)] = raw_1234_4_0_4;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 5)] = raw_1234_4_0_5;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 6)] = raw_1234_4_0_6;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 7)] = raw_1234_4_0_7;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 16)] = raw_1234_4_0_16;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 17)] = raw_1234_4_0_17;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 18)] = raw_1234_4_0_18;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 19)] = raw_1234_4_0_19;
        attributeRawData[Attribute(NwkAddr(1234), EndpointID(4), ClusterID(0), 20)] = raw_1234_4_0_20;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 0)] = raw_1234_4_0_0;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 1)] = raw_1234_4_0_1;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 2)] = raw_1234_4_0_2;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 3)] = raw_1234_4_0_3;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 4)] = raw_1234_4_0_4;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 5)] = raw_1235_7_0_5;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 6)] = raw_1234_4_0_6;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 7)] = raw_1234_4_0_7;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 16)] = raw_1234_4_0_16;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 17)] = raw_1234_4_0_17;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 18)] = raw_1234_4_0_18;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 19)] = raw_1234_4_0_19;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(0), 20)] = raw_1234_4_0_20;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(7), ClusterID(6), 0)] = raw_1235_7_6_0;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 0)] = raw_1234_4_0_0;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 1)] = raw_1234_4_0_1;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 2)] = raw_1234_4_0_2;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 3)] = raw_1234_4_0_3;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 4)] = raw_1234_4_0_4;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 5)] = raw_1235_11_0_5;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 6)] = raw_1234_4_0_6;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 7)] = raw_1234_4_0_7;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 16)] = raw_1234_4_0_16;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 17)] = raw_1234_4_0_17;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 18)] = raw_1234_4_0_18;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 19)] = raw_1234_4_0_19;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(0), 20)] = raw_1234_4_0_20;
        attributeRawData[Attribute(NwkAddr(1235), EndpointID(11), ClusterID(6), 0)] = raw_1235_11_6_0;

        attributeRawData[Attribute(NwkAddr(1235), EndpointID(5), ClusterID(1026), 0)] = raw_1235_5_1026_0;
        attributeRawData[Attribute(NwkAddr(1232), EndpointID(7), ClusterID(1026), 0)] = raw_1232_7_1026_0;

    }

}

