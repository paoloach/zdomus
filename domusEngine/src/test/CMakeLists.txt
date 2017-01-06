cmake_minimum_required(VERSION 2.8)
project(domus_engine_test)

find_package(PostgreSQL)

SET(SOURCE_SRC main.cpp)
file(GLOB test "*.cpp")
file(GLOB testZigbeeData "ZigbeeData/*.cpp")
file(GLOB testIO "IO/*.cpp")
file(GLOB testUtils "Utils/*.cpp")
file(GLOB testMocksHttp "Mocks/http/*.cpp")
file(GLOB testComand "Comand/*.cpp")
file(GLOB testConfiguration "Configuration/*.cpp")
file(GLOB testDatabase "Database/*.cpp")
file(GLOB testJavascriptAttributes "Javascript/JSAttributes/*.cpp")
file(GLOB testHttpServer "httpServer/*.cpp")
file(GLOB testRestParser "httpServer/RestParser/*.cpp")


SET(SRC_TEST_SERIAL_DRIVER serialDriver/IEEEAddressResponseSerialExecutorTest.cpp
        serialDriver/IEEEAddressResponseSerialExecutorTest.h)

SET(SRC_TEST_JAVASCRIPT Javascript/ClusterCmdArgumentMatcher.h Javascript/ClusterCmdArrayArgumentMatcher.h
        Javascript/JavaScriptExecuterTest.cpp Javascript/JavaScriptExecuterTest.h
        Javascript/JSBaseTest.cpp Javascript/JSEndpointTest.h
        Javascript/JSDBTableTest.cpp Javascript/JSDBTableTest.h
        Javascript/JSDevicesTest.cpp Javascript/JSDevicesTest.h
        Javascript/JSDeviceTest.cpp Javascript/JSDeviceTest.h
        Javascript/JSEndpointsTest.cpp Javascript/JSEndpointsTest.h
        Javascript/JSEndpointTest.h Javascript/JSEndpointTest.cpp
        Javascript/JSLogTest.cpp Javascript/JSLogTest.h
        Javascript/JSRowTest.cpp Javascript/JSRowTest.h
        Javascript/JSTest.cpp Javascript/JSTest.h
        Javascript/JSZClusterTest.cpp Javascript/JSZClusterTest.h)

SET(SRC_TEST_MOCK Mocks/AttributeDataContainerMock.cpp Mocks/AttributeDataContainerMock.h
        Mocks/ClusterMock.cpp Mocks/ClusterMock.h
        Mocks/ClustersMock.cpp Mocks/ClustersMock.h
        Mocks/ClusterTypeFactoryMock.cpp Mocks/ClusterTypeFactoryMock.h
        Mocks/ComandMock.cpp Mocks/ComandMock.h
        Mocks/DBTableFactoryMock.cpp Mocks/DBTableFactoryMock.h
        Mocks/DBTableMock.cpp Mocks/DBTableMock.h
        Mocks/JSZClusterMock.cpp Mocks/JSZClusterMock.h
        Mocks/JSZAttributeFactoryMock.cpp Mocks/JSZAttributeFactoryMock.h
        Mocks/JSZAttributeMock.cpp Mocks/JSZAttributeMock.cpp
        Mocks/JSZEndpointMock.cpp Mocks/JSZAttributeMock.h
        Mocks/JSZDeviceMock.cpp Mocks/JSZDeviceMock.h
        Mocks/JSZEndpointMock.cpp Mocks/JSZEndpointMock.h
        Mocks/SingletonObjectsMock.cpp Mocks/SingletonObjectsMock.h
        Mocks/ZCLAttributeMock.cpp Mocks/ZCLAttributeMock.h
        Mocks/ZCLbitmap8bitAttributeMock.cpp Mocks/ZCLbitmap8bitAttributeMock.h
        Mocks/ZCLbooleanAttributeMock.cpp Mocks/ZCLbooleanAttributeMock.h
        Mocks/ZCLenum8bitAttributeMock.cpp Mocks/ZCLenum8bitAttributeMock.h
        Mocks/ZCLIEEEAddressAttributeMock.cpp Mocks/ZCLIEEEAddressAttributeMock.h
        Mocks/ZCLint16AttributeMock.cpp Mocks/ZCLint16AttributeMock.h
        Mocks/ZCLstringAttributeMock.cpp Mocks/ZCLstringAttributeMock.h
        Mocks/ZCLUint8AttributeMock.cpp Mocks/ZCLUint8AttributeMock.cpp
        Mocks/ZCLUint16AttributeMock.cpp Mocks/ZCLUint16AttributeMock.h
        Mocks/ZCLUInt24AttributeMock.cpp Mocks/ZCLUInt24AttributeMock.h
        Mocks/ZDevicesMock.cpp Mocks/ZDevicesMock.h
        Mocks/ZigbeeDeviceMock.cpp Mocks/ZigbeeDeviceMock.h)

set(V8_DIR  ${CMAKE_BINARY_DIR}/v8)
set(V8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/include)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V8_LIB_DIR ${V8_DIR}/lib_x64.debug)
    set(V8_LIBRARY
            v8_libplatform
            v8_libbase
            icui18n
            icuuc
            v8
            )
else()
    if (CMAKE_C_COMPILER MATCHES "arm")
        set(Boost_USE_STATIC_LIBS        ON)
        set(V8_LIB_DIR ${V8_DIR}/lib_arm.release)
        set(V8_LIBRARY
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libicui18n.a
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libicuuc.a
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libv8_base.a
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libv8_external_snapshot.a
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libv8_libbase.a
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libv8_libplatform.a
                ${CMAKE_CURRENT_SOURCE_DIR}/../../v8/lib_arm.release/libv8_libsampler.a
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

set(GMOCK_DIR ${CMAKE_SOURCE_DIR}/googletest/googlemock)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/googletest/googletest)
set(GMOCK_INCLUDE_DIR ${GMOCK_DIR}/include)
set(GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set(GMOCK_LIB_DIR ${GMOCK_DIR}/lib/.libs)
set(GTEST_LIB_DIR ${GTEST_DIR}/lib/.libs)
set(GTEST_LIBS gtest gtest_main)
set(GMOCK_LIBS ${GTEST_LIBS} gmock gmock_main)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g3 -O0 -std=c++14 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g3 -O0  -std=c++14 -Wall -Wextra -Wpedantic ")

include_directories(${CMAKE_SOURCE_DIR}/include ${LIBUSB_INCLUDE_DIR} ${PostgreSQL_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS} ${V8_INCLUDE_DIR} ${ZIGBEELIB_INCLUDE_DIR} ${V8_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})
link_directories(${ZIGBEELIB_LIB_DIR} ${V8_LIB_DIR})


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
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-release/snapshot_blob.cpp)
    else ()
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/snapshot_blob.cpp )
    endif ()
endif ()

add_executable(domus_engine_test
        main.cpp
        ${SRC_TEST_JAVASCRIPT}
        ${testZigbeeData}
        ${testIO}
        ${testUtils}
        ${SRC_TEST_MOCK}
        ${testComand}
        ${SRC_TEST_SERIAL_DRIVER}
        #        ${testDatabase}
        ${testConfiguration}
        ${testJavascriptAttributes}
        ${testHttpServer}
        ${testMocksHttp}
        ${testRestParser}
        ${V8_BLOB}
        )


SET(LIBS zigbeeLib
        usb-1.0
        pq
        PocoNet
        PocoUtil
        PocoXML
        #       PocoZip
        #       PocoData
        PocoFoundation
        ${V8_LIBRARY}
        ${Boost_THREAD_LIBRARY_RELEASE}
        ${Boost_SYSTEM_LIBRARY_RELEASE}
        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
        ${Boost_LOG_LIBRARY_RELEASE}
        ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}
        dl
        pthread
        )

target_link_libraries(domus_engine_test domus_engine_static_lib ${V8_LIBRARY} ${LIBS} ${GMOCK_LIBS})

set_property(TARGET domus_engine_test PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)
