cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_library(property_tree_lib OBJECT
        AttributePT.cpp AttributePT.h
        ClusterPT.cpp ClusterPT.h
        ZDevicePT.cpp ZDevicePT.h
        ZDevicesPT.cpp ZDevicesPT.h
        ZEndpointPT.cpp ZEndpointPT.h)

target_include_directories(property_tree_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} )
