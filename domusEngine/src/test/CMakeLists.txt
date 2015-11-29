cmake_minimum_required (VERSION 2.8)
project (domus_engine_test)

find_package(PostgreSQL)

SET(SOURCE_SRC main.cpp)
file (GLOB test  "*.cpp")
file (GLOB testZigbeeData  "ZigbeeData/*.cpp")
file (GLOB testIO  "IO/*.cpp")
file (GLOB testUtils  "Utils/*.cpp")
file (GLOB testMocks  "Mocks/*.cpp")
file (GLOB testMocksHttp  "Mocks/http/*.cpp")
file (GLOB testComand  "Comand/*.cpp")
file (GLOB testConfiguration  "Configuration/*.cpp")
file (GLOB testDatabase  "Database/*.cpp")
file (GLOB testJavascript  "Javascript/*.cpp")
file (GLOB testJavascriptAttributes  "Javascript/JSAttributes/*.cpp" )
file (GLOB testHttpServer "httpServer/*.cpp")
file (GLOB testRestParser "httpServer/RestParser/*.cpp")

set (V8_DIR /usr/local/v8)
set (V8_INCLUDE_DIR ${V8_DIR}  ${V8_DIR}/include)
set (V8_LIB_DIR ${V8_DIR}/lib)
set (ZIGBEE_LIB_DIR /usr/local/zigbee)
set (ZIGBEELIB_INCLUDE_DIR ${ZIGBEE_LIB_DIR}/include)
set (ZIGBEELIB_LIB_DIR ${ZIGBEE_LIB_DIR}/lib)

set (GMOCK_DIR ${CMAKE_SOURCE_DIR}/googletest/googlemock)
set (GTEST_DIR ${CMAKE_SOURCE_DIR}/googletest/googletest)
set (GMOCK_INCLUDE_DIR ${GMOCK_DIR}/include)
set (GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set (GMOCK_LIB_DIR ${GMOCK_DIR}/lib/.libs)
set (GTEST_LIB_DIR ${GTEST_DIR}/lib/.libs)
set (GTEST_LIBS gtest gtest_main)
set (GMOCK_LIBS ${GTEST_LIBS} gmock gmock_main)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g3 -O2 -std=c++14 ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g3 -O0  -std=c++14 -Wall -Wextra -Wpedantic ")

include_directories( ${LIBUSB_INCLUDE_DIR} ${PostgreSQL_INCLUDE_DIRS} ${PostgreSQL_INCLUDE_DIRS} ${V8_INCLUDE_DIR}  ${ZIGBEELIB_INCLUDE_DIR} ${V8_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} ${GMOCK_INCLUDE_DIR})
link_directories( ${ZIGBEELIB_LIB_DIR} ${V8_LIB_DIR})

add_executable(domus_engine_test
        main.cpp
        ${testJavascript}
        ${testZigbeeData}
        ${testIO}
        ${testUtils}
        ${testMocks}
        ${testComand}
        ${testDatabase}
        ${testConfiguration}
        ${testJavascriptAttributes}
        ${testHttpServer}
        ${testMocksHttp}
        ${testRestParser}
        )

set (V8_LIBRARY
        ${V8_LIB_DIR}/libv8_libplatform.a
        ${V8_LIB_DIR}/libv8_base.a
        ${V8_LIB_DIR}/libv8_libbase.a
        ${V8_LIB_DIR}/libv8_snapshot.a
        ${V8_LIB_DIR}/libicui18n.a
        ${V8_LIB_DIR}/libicuuc.a
        ${V8_LIB_DIR}/libicudata.a
        )

target_link_libraries(domus_engine_test domus_engine_static_lib ${V8_LIBRARY} ${LIBS}  ${GMOCK_LIBS})

set_property(TARGET domus_engine_test PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)