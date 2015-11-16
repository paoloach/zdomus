cmake_minimum_required(VERSION 2.8)
project(zigbee_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

add_subdirectory(googletest/googlemock)
add_subdirectory(src/test)
add_subdirectory(src/zcl)

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

set (USB_HEADER src/usb/USBDevice.h src/usb/usbConfig.h)
file (GLOB zigbee_header  "src/zigbee/*.h")
file (GLOB zigbee_messageStructure_header  "src/zigbee/messageStructure/*.h")
file (GLOB zcl_header  "src/zcl/*.h")
file (GLOB zcl_exceptions  "src/zcl/exceptions/*.h")
file (GLOB zcl_CmdParams_header  "src/zcl/CmdParams/*.h")
file (GLOB attributeTypes_header  "src/zcl/attributeTypes/*.h")
file (GLOB clusterTypes_header  "src/zcl/clusterTypes/*.h")

include_directories(/usr/include/libusb-1.0 . ${PROJECT_SOURCE_DIR}/src)

add_library(zigbeeLib SHARED  ${SOURCE_FILES}  $<TARGET_OBJECTS:ZCL> $<TARGET_OBJECTS:ZCL_Attribute> $<TARGET_OBJECTS:ZCL_Clusters> )
#add_dependencies(zigbeeLib ZCL)

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
