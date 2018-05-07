cmake_minimum_required(VERSION 2.8)
project(zigbee_lib)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fPIC -DBOOST_ALL_DYN_LINK -g3")

find_package(Boost 1.63 COMPONENTS system thread signals program_options filesystem log fiber REQUIRED)

set(GMOCK_DIR googletest/googlemock)
set(GTEST_DIR googletest/googletest)
set(GMOCK_INCLUDE_DIR ${GMOCK_DIR}/include)
set(GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set(GMOCK_LIB_DIR ${GMOCK_DIR}/lib/.libs)
set(GTEST_LIB_DIR ${GTEST_DIR}/lib/.libs)
set(GTEST_LIBS gtest gtest_main)
set(GMOCK_LIBS ${GTEST_LIBS} gmock gmock_main)


add_subdirectory(googletest/googlemock)

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
        src/zigbee/Callbacks.h
        src/zigbee/EndpointID.h
        src/zigbee/NwkAddr.h
        src/zigbee/zigbeeConfig.h
        src/zigbee/ZigbeeDevice.cpp
        src/zigbee/ZigbeeDevice.h
        src/zigbee/ZigbeeTypes.h
        src/zigbee/ExtAddress.h src/zigbee/ExtAddress.cpp
        src/zigbee/messageStructure/ReadAttributeResponseErrorMsg.h
        src/zigbee/ZigbeeTypes.cpp
        src/zigbee/messageStructure/UnbindRequest.h
        src/zigbee/ResponseCallback.h
        src/zigbee/AttributeKey.cpp src/zigbee/AttributeKey.h
        src/zigbee/AttributesKey.cpp src/zigbee/AttributesKey.h
        src/zigbee/AttributesResponseCallback.h src/zigbee/AttributesResponseQueue.cpp src/zigbee/AttributesResponseQueue.h src/zigbee/ResponsesCallbacks.cpp src/zigbee/ResponsesCallbacks.h src/zigbee/CmdData.h src/zigbee/messageStructure/NodeDescriptorResponse.h src/zcl/exceptions/NoValidBandFrequencyException.h)


SET(SOURCE_ZCL_FILES
        src/zcl/impl/ClusterImpl.cpp
        src/zcl/ClusterTypeFactory.cpp
        src/zcl/OnOffLight.cpp
        src/zcl/impl/ZCLAttributeImpl.cpp src/zcl/impl/ZCLAttributeImpl.h
        src/zcl/ZCLAttribute.h
        src/zcl/ZCLDevice.cpp
        src/zcl/ZclAttributeUtils.cpp src/zcl/ZclAttributeUtils.h
        src/zcl/ZCLDataType.h
        src/zcl/StatusEnum.h
        src/zcl/ClustersEnum.h
        src/zigbee/PowerNodeData.h
        src/zigbee/ResponseCallbacks.h
        src/zigbee/ResponseQueue.h
        src/zigbee/CmdData.h)

SET(SOURCE_ATTRIBUTES_FILES
        src/zcl/attributeTypes/implementation/ZCLbitmap8bitAttribute.cpp
        src/zcl/attributeTypes/implementation/ZCLbitmap8bitAttribute.h
        src/zcl/attributeTypes/implementation/ZCLbooleanAttributeImpl.cpp   src/zcl/attributeTypes/implementation/ZCLbooleanAttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLenum8bitAttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLIEEEAddressAttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLint16AttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLStringAttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLuint8AttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLuint16AttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLuint24AttributeImpl.cpp
        src/zcl/attributeTypes/implementation/ZCLuint48AttributeImpl.cpp      src/zcl/attributeTypes/implementation/ZCLuint48AttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLint24AttributeImpl.cpp       src/zcl/attributeTypes/implementation/ZCLint24AttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLUTCTimeImpl.cpp              src/zcl/attributeTypes/implementation/ZCLUTCTimeImpl.h
        src/zcl/attributeTypes/implementation/ZCLOctetStringImp.cpp           src/zcl/attributeTypes/implementation/ZCLOctetStringImp.h
        src/zcl/attributeTypes/implementation/ZCLBitmap32bitAttributeImpl.cpp src/zcl/attributeTypes/implementation/ZCLBitmap32bitAttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLuint32AttributeImpl.cpp      src/zcl/attributeTypes/implementation/ZCLuint32AttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLint32AttributeImpl.cpp       src/zcl/attributeTypes/implementation/ZCLint32AttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLBitmap16bitAttributeImpl.cpp src/zcl/attributeTypes/implementation/ZCLBitmap16bitAttributeImpl.h
        src/zcl/attributeTypes/implementation/ZCLint8AttributeImpl.cpp        src/zcl/attributeTypes/implementation/ZCLint8AttributeImpl.h
        src/zcl/attributeTypes/AttributeValue.h
        src/zcl/attributeTypes/ZCLStringAttribute.h
        src/zcl/attributeTypes/ZCLOctectString.h
        src/zcl/attributeTypes/ZCLEnum8bitAttribute.h
        src/zcl/attributeTypes/ZCLBitmap16bitAttribute.h
        src/zcl/attributeTypes/ZCLBitmap32bitAttribute.h
        src/zcl/attributeTypes/ZCLBooleanAttribute.h
        src/zcl/exceptions/NoBoolException.h
        src/zcl/attributeTypes/ZCLbitmap8bitAttribute.h
        src/zcl/attributeTypes/ZCLIEEEAddressAttribute.h
        src/zcl/attributeTypes/ZCLint8Attribute.h
        src/zcl/attributeTypes/ZCLint16Attribute.h
        src/zcl/attributeTypes/ZCLint24Attribute.h
        src/zcl/attributeTypes/ZCLint32Attribute.h
        src/zcl/attributeTypes/ZCLuint8Attribute.h
        src/zcl/attributeTypes/ZCLuint16Attribute.h
        src/zcl/attributeTypes/ZCLuint24Attribute.h
        src/zcl/attributeTypes/ZCLuint32Attribute.h
        src/zcl/attributeTypes/ZCLuint48Attribute.h
        src/zcl/attributeTypes/ZCLUTCTime.h
        src/zigbee/messageStructure/ActiveEPErrorMessage.h
        src/zigbee/messageStructure/InfoMessage.h
        src/zigbee/messageStructure/DeviceInfoMessage.h
        src/zigbee/messageStructure/ReqDeviceInformation.h
        src/zigbee/messageStructure/IEEEAddressRequestMessage.h
        src/zigbee/messageStructure/IEEEAddressResponse.h
        src/zigbee/messageStructure/LqiResponse.h
        src/zcl/exceptions/ZCLAttributeNotAvailableException.h )


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
        src/zcl/clusterTypes/RelativeHumidityMeasurementCluster.cpp
        src/zcl/clusterTypes/ScenesCluster.cpp
        src/zcl/clusterTypes/TestCluster.cpp
        src/zcl/clusterTypes/TemperatureMeasurementCluster.cpp src/zcl/clusterTypes/ElectricalMeasurementCluster.cpp src/zcl/clusterTypes/ElectricalMeasurementCluster.h src/zcl/Cluster.h)


SET(zigbeeSrcTest src/test/main.cpp
        src/test/ZCLTypeTest.cpp
        src/test/ZCLTypeTest.h
        src/test/attributesTest.cpp src/zcl/ZclAttributeUtils.cpp src/zcl/ZclAttributeUtils.h)


set(USB_HEADER src/usb/USBDevice.h src/usb/usbConfig.h)
file(GLOB zigbee_header "src/zigbee/*.h")
file(GLOB zigbee_messageStructure_header "src/zigbee/messageStructure/*.h")
file(GLOB zcl_header "src/zcl/*.h")
file(GLOB zcl_CmdParams_header "src/zcl/CmdParams/*.h")
file(GLOB attributeTypes_header "src/zcl/attributeTypes/*.h")
file(GLOB clusterTypes_header "src/zcl/clusterTypes/*.h")

SET(zcl_exceptions
        src/zcl/exceptions/NoBoolException.h
        src/zcl/exceptions/NoInt32Exception.h
        src/zcl/exceptions/NoStringException.h
        src/zcl/exceptions/NoUInt64Exception.h
        src/zcl/exceptions/NoUintException.h
        src/zcl/exceptions/NoVectorUInt8Exception.h
        src/zcl/exceptions/ZCLAttributeNotAvailableException.h
        src/zcl/exceptions/AttributeNotFoundException.h
        src/zcl/exceptions/NoValidLogicalTypeException.h
        src/zcl/exceptions/NoValidBandFrequencyException.h)

include_directories(/usr/include/libusb-1.0 . ${PROJECT_SOURCE_DIR}/src ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})


add_library(ZCL_Commons OBJECT ${SOURCE_ZCL_FILES})
add_library(Attributes OBJECT ${SOURCE_ATTRIBUTES_FILES})
add_library(Clusters OBJECT ${SOURCE_CLLUSTER_FILES})
add_library(zigbeeLib SHARED
        ${SOURCE_FILES}
        $<TARGET_OBJECTS:ZCL_Commons>
        $<TARGET_OBJECTS:Attributes>
        $<TARGET_OBJECTS:Clusters>)

add_executable(zigbeeLibTest ${zigbeeSrcTest})

#target_include_directories(zigbeeLibTest ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})

target_link_libraries(zigbeeLibTest ${GMOCK_LIBS} zigbeeLib ${Boost_SIGNALS_LIBRARY_RELEASE}
        ${Boost_THREAD_LIBRARY_RELEASE}
        ${Boost_SYSTEM_LIBRARY_RELEASE}
        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
        ${Boost_LOG_LIBRARY_RELEASE}
        ${Boost_FIBER_LIBRARY_RELEASE}
        ${Boost_CONTEXT_LIBRARY_RELEASE}
        ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE} pthread)


target_link_libraries(zigbeeLib usb-1.0 ${Boost_LOG_LIBRARY_RELEASE})

set_property(TARGET zigbeeLib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)

set(headers ${USB_HEADER}
        ${zigbee_messageStructure_header}
        ${zigbee_header}
        ${zcl_header}
        ${zcl_exceptions}
        ${zcl_CmdParams_header}
        ${attributeTypes_header}
        ${clusterTypes_header})

set_target_properties(zigbeeLib PROPERTIES  PUBLIC_HEADER "${headers}" )

set(INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/zigbee)
#set(INSTALL_PATH /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot/usr/local/zigbee)
set(INSTALL_LIB_DIR ${INSTALL_PATH}/lib)
set(INSTALL_INCLUDE_DIR ${INSTALL_PATH}/include)

#SET(INSTALL_INCLUDE_DIR "/opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot/usr/local/zigbee/include")
#SET(INSTALL_LIB_DIR "/opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot/usr/local/zigbee/lib")

message("install path: ${INSTALL_PATH}")
message("install lib dir: ${INSTALL_LIB_DIR}")
message("install include dir: ${INSTALL_INCLUDE_DIR}")



INSTALL(TARGETS zigbeeLib
        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
        PUBLIC_HEADER DESTINATION  ${INSTALL_INCLUDE_DIR})

INSTALL(FILES ${zigbee_header} DESTINATION ${INSTALL_INCLUDE_DIR}/zigbee)
INSTALL(FILES ${zcl_header} DESTINATION ${INSTALL_INCLUDE_DIR}/zcl)
INSTALL(FILES ${zcl_exceptions} DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/exceptions)
INSTALL(FILES ${zcl_CmdParams_header} DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/CmdParams)
INSTALL(FILES ${attributeTypes_header} DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/attributeTypes)
INSTALL(FILES ${clusterTypes_header} DESTINATION ${INSTALL_INCLUDE_DIR}/zcl/clusterTypes)

INSTALL(FILES ${zigbee_messageStructure_header} DESTINATION ${INSTALL_INCLUDE_DIR}/zigbee/messageStructure)
INSTALL(FILES ${USB_HEADER} DESTINATION ${INSTALL_INCLUDE_DIR}/usb)
