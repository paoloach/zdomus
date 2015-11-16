cmake_minimum_required(VERSION 2.8)
project(zigbee_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

add_subdirectory(googletest/googlemock)
add_subdirectory(src/test)

set(INSTALL_PATH /usr/local/zigbee)
set(INSTALL_LIB_DIR ${INSTALL_PATH}/lib)
set(INSTALL_INCLUDE_DIR ${INSTALL_PATH}/include)

ADD_CUSTOM_TARGET(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)


set(SOURCE_FILES
    src/usb/usbConfig.h
    src/usb/USBDevice.cpp
    src/usb/USBDevice.h
    src/zigbee/messageStructure/AnnunceMessage.h
    src/zigbee/messageStructure/AttributeValue.h
    src/zigbee/messageStructure/BindRequest.h
    src/zigbee/messageStructure/BindTableResponseMessage.h
    src/zigbee/messageStructure/ComandSend.h
    src/zigbee/messageStructure/GenericMessage.h
    src/zigbee/messageStructure/ReadAttributeResponseMessage.h
    src/zigbee/messageStructure/ReqActiveEndpointsMessage.h
    src/zigbee/messageStructure/ReqBindTable.h
    src/zigbee/messageStructure/SimpleDescMessage.h
    src/zigbee/messageStructure/WriteAttributeValue.h
    src/zigbee/messageStructure/ZAddrType.h
    src/zigbee/AttributeStatusRecord.h
    src/zigbee/ClusterID.cpp
    src/zigbee/ClusterID.h
    src/zigbee/EndpointID.h
    src/zigbee/NwkAddr.h
    src/zigbee/zigbeeConfig.h
    src/zigbee/ZigbeeDevice.cpp
    src/zigbee/ZigbeeDevice.h
    src/zigbee/ZigbeeTypes.h)


SET(SOURCE_ZCL_FILES
        src/zcl/Cluster.cpp
        src/zcl/ClusterTypeFactory.cpp
        src/zcl/OnOffLight.cpp
        src/zcl/ZCLAttribute.cpp
        src/zcl/ZCLDevice.cpp)

SET(SOURCE_ATTRIBUTES_FILES
        src/zcl/attributeTypes/ZCLbitmap8bitAttribute.cpp
        src/zcl/attributeTypes/ZCLbooleanAttribute.cpp
        src/zcl/attributeTypes/ZCLenum8bitAttribute.cpp
        src/zcl/attributeTypes/ZCLIEEEAddressAttribute.cpp
        src/zcl/attributeTypes/ZCLint16Attribute.cpp
        src/zcl/attributeTypes/ZCLstringAttribute.cpp
        src/zcl/attributeTypes/ZCLuint8Attribute.cpp
        src/zcl/attributeTypes/ZCLuint16Attribute.cpp
        src/zcl/attributeTypes/ZCLuint24Attribute.cpp)


SET(SOURCE_CLLUSTER_FILES
        src/zcl/clusterTypes/BasicCluster.cpp
        src/zcl/clusterTypes/DeviceTemperatureConfiguration.cpp
        src/zcl/clusterTypes/FlowMeasurementCluster.cpp
        src/zcl/clusterTypes/GroupsCluster.cpp
        src/zcl/clusterTypes/IdentifyCluster.cpp
        src/zcl/clusterTypes/IlluminanceLevelSensingCluster.cpp
        src/zcl/clusterTypes/IlluminanceMeasurementCluster.cpp
        src/zcl/clusterTypes/LevelControlCluster.cpp
        src/zcl/clusterTypes/MeteringCluster.cpp
        src/zcl/clusterTypes/NullCluster.cpp
        src/zcl/clusterTypes/OccupancySensingCluster.cpp
        src/zcl/clusterTypes/OnOffCluster.cpp
        src/zcl/clusterTypes/PowerConfigurationCluster.cpp
        src/zcl/clusterTypes/PressureMeasurementCluster.cpp
        src/zcl/clusterTypes/RelativeHumidityMeasuramentCluster.cpp
        src/zcl/clusterTypes/ScenesCluster.cpp
        src/zcl/clusterTypes/TemperatureMeasurementCluster.cpp)


set (USB_HEADER src/usb/USBDevice.h src/usb/usbConfig.h)
file (GLOB zigbee_header  "src/zigbee/*.h")
file (GLOB zigbee_messageStructure_header  "src/zigbee/messageStructure/*.h")
file (GLOB zcl_header  "src/zcl/*.h")
file (GLOB zcl_exceptions  "src/zcl/exceptions/*.h")
file (GLOB zcl_CmdParams_header  "src/zcl/CmdParams/*.h")
file (GLOB attributeTypes_header  "src/zcl/attributeTypes/*.h")
file (GLOB clusterTypes_header  "src/zcl/clusterTypes/*.h")

include_directories(/usr/include/libusb-1.0 . ${PROJECT_SOURCE_DIR}/src)

add_library(ZCL_Commons OBJECT  ${SOURCE_ZCL_FILES}  )
add_library(Attributes OBJECT ${SOURCE_ATTRIBUTES_FILES} )
add_library(Clusters OBJECT  ${SOURCE_CLLUSTER_FILES}  )
add_library(zigbeeLib SHARED  ${SOURCE_FILES}  $<TARGET_OBJECTS:ZCL_Commons>  $<TARGET_OBJECTS:Attributes> $<TARGET_OBJECTS:Clusters> )

target_link_libraries(zigbeeLib usb-1.0)

set_property(TARGET zigbeeLib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)
set_target_properties(zigbeeLib PROPERTIES PUBLIC_HEADER "${zigbee_header}" )


INSTALL(TARGETS zigbeeLib  LIBRARY DESTINATION  ${INSTALL_LIB_DIR} )
INSTALL(FILES ${zigbee_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zigbee )
INSTALL(FILES ${zcl_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl )
INSTALL(FILES ${zcl_exceptions}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/exceptions )
INSTALL(FILES ${zcl_CmdParams_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/CmdParams )
INSTALL(FILES ${attributeTypes_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/attributeTypes )
INSTALL(FILES ${clusterTypes_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/clusterTypes )
INSTALL(FILES ${zigbee_messageStructure_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zigbee/messageStructure )
INSTALL(FILES ${USB_HEADER}  DESTINATION ${INSTALL_INCLUDE_DIR}/usb)
