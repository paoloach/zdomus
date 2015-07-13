cmake_minimum_required (VERSION 2.6)
project (zigbee_lib)

set(CMAKE_BUILD_TYPE Debug)
set(INSTALL_PATH /usr/local/zigbee)
set(INSTALL_LIB_DIR ${INSTALL_PATH}/lib)
set(INSTALL_INCLUDE_DIR ${INSTALL_PATH}/include)

set (GMOCK_DIR /home/paolo/workspace_luna/gmock-1.7.0)
set (GTEST_DIR /home/paolo/workspace_luna/gmock-1.7.0/gtest)
set (GMOCK_INCLUDE_DIR ${GMOCK_DIR}/include)
set (GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set (GMOCK_LIB_DIR ${GMOCK_DIR}/lib/.libs)
set (GTEST_LIB_DIR ${GTEST_DIR}/lib/.libs)
set (GTEST_LIBS gtest gtest_main)
set (GMOCK_LIBS ${GTEST_LIBS} gmock gmock_main)

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)


set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g3 -O2 -std=c++14")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g3 -O0  -std=c++14")

#find_package(Boost 1.42 COMPONENTS system filesystem thread date_time regex REQUIRED)

file (GLOB zigbee_src  "src/zigbee/*.cpp")
file (GLOB zcl_src  "src/zcl/*.cpp")
file (GLOB attributeTypes_src  "src/zcl/attributeTypes/*.cpp")
file (GLOB clusterTypes_src  "src/zcl/clusterTypes/*.cpp")
file (GLOB usb_src  "src/usb/*.cpp")

file (GLOB zigbeeSrcTest "src/test/*.cpp") 

set (USB_HEADER src/usb/USBDevice.h src/usb/usbConfig.h)
file (GLOB zigbee_header  "src/zigbee/*.h")
file (GLOB zigbee_messageStructure_header  "src/zigbee/messageStructure/*.h")
file (GLOB zcl_header  "src/zcl/*.h")
file (GLOB zcl_exceptions  "src/zcl/exceptions/*.h")
file (GLOB zcl_CmdParams_header  "src/zcl/CmdParams/*.h")
file (GLOB attributeTypes_header  "src/zcl/attributeTypes/*.h")
file (GLOB clusterTypes_header  "src/zcl/clusterTypes/*.h")


include_directories( /usr/include/libusb-1.0 . ./src ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})
link_directories(  ${GMOCK_LIB_DIR} ${GTEST_LIB_DIR})

add_library(zigbeeLib SHARED  ${zigbee_src} ${zcl_src} ${attributeTypes_src} ${clusterTypes_src} ${usb_src})

add_executable(zigbeeLibTest
		 src/test/main.cpp
		  ${zigbeeSrcTest}
		  )

target_link_libraries(zigbeeLib usb-1.0)


 
set_property(TARGET zigbeeLib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)
set_target_properties(zigbeeLib PROPERTIES PUBLIC_HEADER "${zigbee_header}" )

target_link_libraries(zigbeeLibTest 
			${GMOCK_LIBS}
			pthread 
			 )

INSTALL(TARGETS zigbeeLib  LIBRARY DESTINATION  ${INSTALL_LIB_DIR} )
INSTALL(FILES ${zigbee_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zigbee )
INSTALL(FILES ${zcl_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl )
INSTALL(FILES ${zcl_exceptions}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/exceptions )
INSTALL(FILES ${zcl_CmdParams_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/CmdParams )
INSTALL(FILES ${attributeTypes_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/attributeTypes )
INSTALL(FILES ${clusterTypes_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/clusterTypes )
INSTALL(FILES ${zigbee_messageStructure_header}  DESTINATION ${INSTALL_INCLUDE_DIR}/zigbee/messageStructure )
INSTALL(FILES ${USB_HEADER}  DESTINATION ${INSTALL_INCLUDE_DIR}/usb)
