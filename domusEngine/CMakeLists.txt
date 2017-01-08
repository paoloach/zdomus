cmake_minimum_required(VERSION 2.8)
project(domus_engine)

add_subdirectory(googletest/googlemock)
add_subdirectory(src/test)


set(V8_DIR ${CMAKE_BINARY_DIR}/v8)
set(V8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/v8/include)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V8_LIB_DIR ${V8_DIR}/lib_x64.debug)
    set(V8_LIBRARY
            v8_libplatform
            v8_libbase
            icui18n
            icuuc
            v8
            )
else ()
    if (CMAKE_C_COMPILER MATCHES "arm")
        set(Boost_USE_STATIC_LIBS        ON)
        set(V8_LIB_DIR ${V8_DIR}/lib_arm.release)
        set(V8_LIBRARY
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libicui18n.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libicuuc.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_base.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_external_snapshot.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_libbase.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_libplatform.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_libsampler.a
                )
    else ()

        set(V8_LIB_DIR ${V8_DIR}/lib_x64.release)
        set(V8_LIBRARY
                v8_libplatform
                v8_libbase
                icui18n
                icuuc
                v8
                )
    endif ()
endif ()


set(ZIGBEE_LIB_DIR ${CMAKE_FIND_ROOT_PATH}/usr/local/zigbee)
set(ZIGBEELIB_INCLUDE_DIR ${ZIGBEE_LIB_DIR}/include)
set(ZIGBEELIB_LIB_DIR ${ZIGBEE_LIB_DIR}/lib)

set(LIBUSB_INCLUDE_DIR ${CMAKE_FIND_ROOT_PATH}/usr/include/libusb-1.0)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g2 -O0 -std=c++14  -Wall -Wextra -Wpedantic -DBOOST_ALL_DYN_LINK  -fno-omit-frame-pointer ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g2 -O0  -std=c++14 -Wall -Wextra -Wpedantic -DBOOST_ALL_DYN_LINK    -fno-omit-frame-pointer  ")

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)

find_package(PostgreSQL)

find_package(Boost COMPONENTS system thread signals program_options filesystem log REQUIRED)

link_directories(${ZIGBEELIB_LIB_DIR} ${V8_LIB_DIR})
include_directories(./include ${LIBUSB_INCLUDE_DIR} ${PostgreSQL_INCLUDE_DIRS} ${ZIGBEELIB_INCLUDE_DIR} ${V8_INCLUDE_DIR})

file(GLOB src "src/*.cpp")
file(GLOB srcZigbeeData "src/ZigbeeData/*.cpp")
file(GLOB srcZigbeeDataPT "src/ZigbeeData/PropertyTree/*.cpp")
file(GLOB srcZigbeeDataExceptions "src/ZigbeeData/Exceptions/*.cpp")
file(GLOB srcComand "src/Comand/*.cpp")
file(GLOB srcIO "src/IO/*.cpp")
file(GLOB srcUtils "src/Utils/*.cpp")
file(GLOB srcDatabase "src/Database/*.cpp")
file(GLOB srcDatabase_exceptions "src/Database/Exceptions/*.cpp")
file(GLOB srcConfiguration "src/Configuration/*.cpp")
file(GLOB srcJavaScript_attributes "src/JavaScript/JSZAttributes/*.cpp")
file(GLOB srcJavaScript_exceptions "src/JavaScript/Exceptions/*.cpp")
file(GLOB srcHttpServer "src/httpServer/*.cpp")
file(GLOB srcRestParser "src/httpServer/RestParser/*.cpp")
file(GLOB srcRestActions "src/httpServer/RestActions/*.cpp")


if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if (CMAKE_C_COMPILER MATCHES "arm")
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-debug/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-debug/snapshot_blob.cpp)
    else ()
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-debug/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-debug/snapshot_blob.cpp)
    endif ()
else ()
    if (CMAKE_C_COMPILER MATCHES "arm")
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-release/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-release/snapshot_blob.cpp src/DataDemo.cpp)
    else ()
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/snapshot_blob.cpp src/DataDemo.cpp)
    endif ()
endif ()


SET(SRC_SERIAL_DRIVER
        src/serialDriver/InvalidResponseSerialExecutor.h
        src/serialDriver/IEEEAddressResponseErrorSerialExecutor.h src/serialDriver/AnnunceSerialExecutor.h
        src/serialDriver/SerialResponseExecutor.cpp src/serialDriver/SerialResponseExecutor.h
        src/serialDriver/SerialExecutor.h
        src/serialDriver/IEEEAddressResponseSerialExecutor.h
        src/serialDriver/SimpleDescSerialExecutor.h
        src/serialDriver/ActiveEndpointErrorExecutor.h
        src/serialDriver/BindTableSerialExecuter.h
        src/serialDriver/ReadAttributeResponseErrorSerial.h
        src/serialDriver/ReadAttributeResponseSerial.h src/serialDriver/DeviceInfoSerialExecutor.h)

set(USB_SRC src/usb/ActiveEPReqError.h
        src/usb/AnnunceMsgExecuter.h
        src/usb/AttributeValueReqError.cpp
        src/usb/AttributeValueReqError.h
        src/usb/AttributeValuesExecuter.h
        src/usb/AttributeValuesSignalMap.h
        src/usb/BindResponse.cpp
        src/usb/BindResponse.h
        src/usb/BindTableExecuter.h
        src/usb/Executor.h
        src/usb/RequestedAttributes.cpp
        src/usb/RequestedAttributes.h
        src/usb/SimpleDescExecutor.h
        src/usb/usbConfig.h
        src/usb/USBDevice.cpp
        src/usb/USBDevice.h
        src/usb/UsbResponseExecutors.cpp
        src/usb/UsbResponseExecutors.h
        src/httpServer/RestActions/UpdateAttributes.cpp
        src/httpServer/RestActions/UpdateAttributes.h
        src/Utils/AttributeWriterResult.cpp
        src/Utils/AttributeWriterResult.h
        src/httpServer/ServerRequest.cpp
        src/httpServer/ServerRequest.h
        src/usb/InfoMessageExecuter.h src/usb/DeviceInfoExecutor.cpp
        src/usb/DeviceInfoExecutor.h
        src/Utils/DeviceInfoDispatcher.cpp src/Utils/DeviceInfoDispatcher.h
        src/httpServer/RestActions/ShowDeviceInfo.cpp src/httpServer/RestActions/ShowDeviceInfo.h
        src/Utils/Constant.cpp src/Utils/Constant.h
        src/usb/IEEEAddressResponseExecutor.h
        src/ZigbeeData/NewDeviceObserver.h
        src/ZigbeeData/TopologyCreation.cpp src/ZigbeeData/TopologyCreation.h
        src/httpServer/RestActions/ShowTopology.cpp src/httpServer/RestActions/ShowTopology.h
        src/usb/UsbDemoData.cpp )


add_library(javascript_lib OBJECT
        src/JavaScript/JavaScriptData.cpp
        src/JavaScript/JavaScriptExecuter.cpp
        src/JavaScript/JSDbManager.cpp
        src/JavaScript/JSDBTable.cpp
        src/JavaScript/JSLog.cpp
        src/JavaScript/JSManager.cpp
        src/JavaScript/JSRestServer.cpp
        src/JavaScript/JSRow.cpp
        src/JavaScript/JSZAttribute.cpp
        src/JavaScript/JSZAttributeFactory.cpp
        src/JavaScript/JSZCluster.cpp
        src/JavaScript/JSZDevice.cpp
        src/JavaScript/JSZDevices.cpp
        src/JavaScript/JSZEndpoint.cpp
        src/JavaScript/V8anyConverter.cpp
        src/JavaScript/V8Allocator.cpp
        src/JavaScript/V8Allocator.h
        src/JavaScript/JSZEndpoints.cpp src/JavaScript/JSZEndpoints.h
        src/JavaScript/GlobalJSFunctions.cpp src/JavaScript/GlobalJSFunctions.h src/JavaScript/JSCallbackFifo.cpp src/JavaScript/JSCallbackFifo.h)

add_library(domus_engine_static_lib STATIC
        ${USB_SRC}
        ${SRC_SERIAL_DRIVER}
        ${srcZigbeeData}
        ${srcZigbeeDataPT}
        ${srcIO}
        ${srcUtils}
        ${srcComand}
        #	${srcJavaScript}
        ${srcConfiguration}
        ${srcZigbeeDataExceptions}
        ${srcJavaScript_attributes}
        ${srcJavaScript_exceptions}
        ${srcDatabase}
        ${srcDatabase_exceptions}
        ${srcHttpServer}
        ${srcRestParser}
        ${srcRestActions}
        $<TARGET_OBJECTS:javascript_lib>
        src/httpServer/RestActions/ShowBindTable.cpp
        src/httpServer/RestActions/ShowBindTable.h
        src/httpServer/RestActions/ExecuteBind.cpp
        src/httpServer/RestActions/ExecuteBind.h
        src/ZigbeeData/Exceptions/InvalidOutCluster.cpp
        src/ZigbeeData/Exceptions/InvalidOutCluster.h
        src/ZigbeeData/Exceptions/InvalidInCluster.cpp
        src/ZigbeeData/Exceptions/InvalidInCluster.h
        src/ZigbeeData/Exceptions/InvalidInCluster.cpp
        src/ZigbeeData/Exceptions/InvalidInCluster.h
        src/ZigbeeData/ZElement.cpp
        src/ZigbeeData/ZElement.h
        src/json/jsoncpp.cpp
        src/json/json/json-forwards.h
        src/json/json/json.h
        src/httpServer/RestActions/ShowAttributeFactory.cpp
        src/httpServer/RestActions/ShowAttributeFactory.h
        src/httpServer/RestParser/RestQuery.cpp
        src/httpServer/RestParser/RestQuery.h
        src/httpServer/RestActions/ExecuteReset.cpp
        src/httpServer/RestActions/ExecuteReset.h
        src/Utils/Clusters.cpp
        src/Utils/Clusters.h src/ZigbeeData/RequestDevices.cpp src/ZigbeeData/RequestDevices.h src/serialDriver/SerialDriver.cpp src/serialDriver/SerialDriver.h)


add_executable(domus_engine src/main.cpp ${V8_BLOB})


SET(LIBS zigbeeLib
        usb-1.0
        pq
        PocoNet
        PocoUtil
        PocoXML
        #con     PocoZip
        #     PocoData
        PocoFoundation
        ${V8_LIBRARY}
        ${Boost_SIGNALS_LIBRARY_RELEASE}
        ${Boost_THREAD_LIBRARY_RELEASE}
        ${Boost_SYSTEM_LIBRARY_RELEASE}
        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
        ${Boost_LOG_LIBRARY_RELEASE}
        ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}
        dl
        pthread
        )

target_link_libraries(domus_engine domus_engine_static_lib ${V8_LIBRARY} ${LIBS})


set_property(TARGET domus_engine_static_lib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build/.lib)
set_property(TARGET domus_engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)

