cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_subdirectory(PropertyTree)

SET(SRC_ZIGBEE_DATA AttributeData.cpp AttributeData.h
        BindTable.cpp BindTable.h
        NewDeviceObserver.h
        RequestDevices.cpp RequestDevices.h
        TopologyCreation.cpp TopologyCreation.h
        ZDevice.cpp ZDevice.h
        ZDevices.cpp ZDevices.h
        ZElement.cpp ZElement.h
        ZEndpoint.cpp ZEndpoint.h
        NewDeviceObserver.h
        TopologyCreation.cpp TopologyCreation.h
        Exceptions/InvalidInCluster.cpp Exceptions/InvalidInCluster.h
        Exceptions/InvalidOutCluster.cpp
        Exceptions/InvalidZDevice.cpp
        Exceptions/InvalidZEndpointException.cpp
        Exceptions/ZigbeeDeviceException.cpp)

message("COMMON_DIR = ${CMAKE_SOURCE_DIR}/include")

add_library(zigbee_data_lib STATIC ${SRC_ZIGBEE_DATA} $<TARGET_OBJECTS:property_tree_lib> )

target_include_directories(zigbee_data_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include )