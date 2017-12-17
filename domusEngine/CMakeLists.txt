cmake_minimum_required(VERSION 3.7)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project(domus_engine)

set(CMAKE_CXX_STANDARD 17)

ExternalProject_Add(pistache
        GIT_REPOSITORY https://github.com/oktal/pistache.git
        GIT_SUBMODULES
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/pistache
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs
        UPDATE_COMMAND "" # Skip annoying updates for every build
        INSTALL_COMMAND ""
        CMAKE_ARGS  -DCMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH}
                -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
                -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                ${USE_PROJECT_CMAKE_MODULE_PATH}
        )

ExternalProject_Get_Property(pistache install_dir)

set(PISTACHE_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/pistache/src/pistache/include )
set(PISTACHE_LIB ${CMAKE_CURRENT_BINARY_DIR}/pistache/src/pistache-build/src/libnet_static.a)


add_subdirectory(googletest/googlemock)
add_subdirectory(src/test)


set(V8_DIR ${CMAKE_BINARY_DIR}/v8)
set(V8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/v8/include ${PISTACHE_INCLUDE_DIR})

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
    if (BUILD_V8_VERSION MATCHES "arm")
        message("Using v8 ARM version")
        set(Boost_USE_STATIC_LIBS ON)
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
        message("Using v8 x64 version")
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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -g0 -O3 -std=c++17  -Wall -Wextra -Wpedantic  -fno-omit-frame-pointer ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g2 -O3 -std=c++17  -Wall -Wextra -Wpedantic -DBOOST_ALL_DYN_LINK  -fno-omit-frame-pointer ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g2 -O0  -std=c++17 -Wall -Wextra -Wpedantic -DBOOST_ALL_DYN_LINK    -fno-omit-frame-pointer  ")

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)

find_package(PostgreSQL)

find_package(Boost 1.63 COMPONENTS fiber context system thread signals program_options filesystem log REQUIRED)

link_directories(${ZIGBEELIB_LIB_DIR} ${V8_LIB_DIR})
include_directories(./include ${LIBUSB_INCLUDE_DIR} ${PostgreSQL_INCLUDE_DIRS} ${ZIGBEELIB_INCLUDE_DIR} ${V8_INCLUDE_DIR})

file(GLOB src "src/*.cpp")
file(GLOB srcZigbeeDataPT "src/ZigbeeData/PropertyTree/*.cpp")
file(GLOB srcZigbeeDataExceptions "src/ZigbeeData/Exceptions/*.cpp")
file(GLOB srcComand "src/Comand/*.cpp")
file(GLOB srcIO "src/IO/*.cpp")
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
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/snapshot_blob.cpp src/DataDemo.cpp src/usb/messages/zigbeeConfig.h)
    endif ()
endif ()



SET(SRC_DATABASE
        src/Database/Exceptions/DBException.h
        src/Database/Exceptions/DBExceptionInvalidDataType.cpp src/Database/Exceptions/DBExceptionInvalidDataType.h
        src/Database/Exceptions/DBExceptionNoServer.cpp src/Database/Exceptions/DBExceptionNoServer.h
        src/Database/Exceptions/DBExceptionNoTable.cpp src/Database/Exceptions/DBExceptionNoTable.h
        src/Database/Exceptions/DBExceptionQueryError.cpp src/Database/Exceptions/DBExceptionQueryError.h
        src/Database/Exceptions/DBExceptionResultNotSet.cpp src/Database/Exceptions/DBExceptionResultNotSet.h
        src/Database/DBDataConverter.cpp src/Database/DBDataConverter.h
        src/Database/DBRow.cpp src/Database/DBRow.h
        src/Database/DBTable.cpp src/Database/DBTable.h
        src/Database/DBTableFactory.cpp src/Database/DBTableFactory.h
        src/Database/ResultSet.cpp src/Database/ResultSet.h)

SET(SRC_ZIGBEE_DATA src/ZigbeeData/AttributeData.cpp src/ZigbeeData/AttributeData.h
        src/ZigbeeData/BindTable.cpp src/ZigbeeData/BindTable.h
        src/ZigbeeData/ExtAddress.cpp src/ZigbeeData/ExtAddress.h
        src/ZigbeeData/IEEEAddressResponse.h
        src/ZigbeeData/NewDeviceObserver.h
        src/ZigbeeData/RequestDevices.cpp src/ZigbeeData/RequestDevices.h
        src/ZigbeeData/TopologyCreation.cpp src/ZigbeeData/TopologyCreation.h
        src/ZigbeeData/ZDevice.cpp src/ZigbeeData/ZDevice.h
        src/ZigbeeData/ZDevices.cpp src/ZigbeeData/ZDevices.h
        src/ZigbeeData/ZElement.cpp src/ZigbeeData/ZElement.h
        src/ZigbeeData/ZEndpoint.cpp src/ZigbeeData/ZEndpoint.h
        src/ZigbeeData/NewDeviceObserver.h
        src/ZigbeeData/TopologyCreation.cpp src/ZigbeeData/TopologyCreation.h)

SET(SRC_EXCEPTION src/Exception/PathNotFound.h src/Exception/Timeout.h)

SET(SRC_HTTP src/httpServer/RestHandler.cpp src/httpServer/RestHandler.h src/httpServer/RestActions/ShowPowerNode.cpp src/httpServer/RestActions/ShowPowerNode.h)


SET(SRC_DEMO_DRIVER
        src/DemoDriver/DemoDevice.cpp src/DemoDriver/DemoDevice.h)


SET(SRC_SERIAL_DRIVER
        src/serialDriver/SerialDriver.cpp src/serialDriver/SerialDriver.h
        src/serialDriver/InvalidResponseSerialExecutor.h
        src/serialDriver/IEEEAddressResponseErrorSerialExecutor.h src/serialDriver/AnnunceSerialExecutor.h
        src/serialDriver/SerialResponseExecutor.cpp src/serialDriver/SerialResponseExecutor.h
        src/serialDriver/SerialExecutor.h
        src/serialDriver/IEEEAddressResponseSerialExecutor.h
        src/serialDriver/SimpleDescSerialExecutor.h
        src/serialDriver/ActiveEndpointErrorExecutor.h
        src/serialDriver/BindTableSerialExecuter.h
        src/serialDriver/ReadAttributeResponseErrorSerial.h
        src/serialDriver/PowerNodeResponseError.cpp src/serialDriver/PowerNodeResponseError.h
        src/serialDriver/ReadAttributeResponseSerial.h
        src/serialDriver/DeviceInfoSerialExecutor.h
        src/serialDriver/PowerNodeResponse.cpp src/serialDriver/PowerNodeResponse.h src/serialDriver/AliveMessage.h)

set(USB_SRC src/usb/ActiveEPReqError.h
        src/usb/AnnunceMsgExecuter.h
        src/usb/AttributeValueReqError.cpp
        src/usb/AttributeValueReqError.h
        src/usb/AttributeValuesExecuter.h
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
        src/usb/InfoMessageExecuter.h src/usb/DeviceInfoExecutor.cpp
        src/usb/DeviceInfoExecutor.h
        src/usb/IEEEAddressResponseExecutor.h
        src/usb/messages/PowerNodeRequestMessage.h
        src/usb/PowerNodeReqError.h
        src/usb/messages/PowerNodeRespMessage.h src/DemoDriver/DemoDriverFactory.h src/usb/UsbDriverFactory.h)


set(SRC_UTILS   src/Utils/AttributeWriterResult.cpp src/Utils/AttributeWriterResult.h
                src/Utils/AttributeWriter.cpp src/Utils/AttributeWriter.h
                src/Utils/Clusters.cpp  src/Utils/Clusters.h
                src/Utils/SingletonObjects.cpp  src/Utils/SingletonObjects.h
                src/Utils/DeviceInfoDispatcher.cpp src/Utils/DeviceInfoDispatcher.h
                src/Utils/Constant.cpp src/Utils/Constant.h
                src/Utils/LogConstants.h
                src/Utils/DriverFactory.h src/Database/ResultSet.cpp src/Database/ResultSet.h)


add_library(javascript_lib OBJECT
        src/JavaScript/JSObjects.h
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
        src/JavaScript/GlobalJSFunctions.cpp src/JavaScript/GlobalJSFunctions.h
        src/JavaScript/JSCallbackFifo.cpp src/JavaScript/JSCallbackFifo.h
        src/JavaScript/JSResultSet.cpp src/JavaScript/JSResultSet.h
        src/JavaScript/JSRestParam.cpp src/JavaScript/JSRestParam.h src/JavaScript/JSBase.h)


add_library(domus_engine_static_lib STATIC
        ${SRC_HTTP}
        ${SRC_UTILS}
        ${SRC_ZIGBEE_DATA}
        ${srcZigbeeDataPT}
        ${srcIO}
        ${srcComand}
        #	${srcJavaScript}
        ${srcConfiguration}
        ${srcZigbeeDataExceptions}
        ${srcJavaScript_attributes}
        ${srcJavaScript_exceptions}
        ${SRC_DATABASE}
        ${srcHttpServer}
        ${srcRestParser}
        ${srcRestActions}
        $<TARGET_OBJECTS:javascript_lib>
        ${SRC_EXCEPTION}
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
        src/ZigbeeData/RequestDevices.cpp src/ZigbeeData/RequestDevices.h
        )


add_executable(domus_engine src/main.cpp ${V8_BLOB} ${SRC_DEMO_DRIVER} ${SRC_SERIAL_DRIVER} ${USB_SRC})

add_dependencies(domus_engine pistache)

SET(LIBS zigbeeLib
        usb-1.0
        pq
        ${V8_LIBRARY}
        ${Boost_SIGNALS_LIBRARY_RELEASE}
        ${Boost_THREAD_LIBRARY_RELEASE}
        ${Boost_SYSTEM_LIBRARY_RELEASE}
        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
        ${Boost_LOG_LIBRARY_RELEASE}
        ${Boost_LOG_SETUP_LIBRARY_RELEASE}
        ${Boost_CONTEXT_LIBRARY}
        ${Boost_FIBER_LIBRARY_RELEASE}
        ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}
        ${PISTACHE_LIB}
        dl
        pthread
        )

target_link_libraries(domus_engine domus_engine_static_lib ${V8_LIBRARY} ${LIBS})


set_property(TARGET domus_engine_static_lib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build/.lib)
set_property(TARGET domus_engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)

