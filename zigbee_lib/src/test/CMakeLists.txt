cmake_minimum_required(VERSION 2.8)
project(zigbee_lib_test)

set (GMOCK_DIR ../../googletest/googlemock)
set (GTEST_DIR ../../googletest/googletest)
set (GMOCK_INCLUDE_DIR ${GMOCK_DIR}/include)
set (GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set (GMOCK_LIB_DIR ${GMOCK_DIR}/lib/.libs)
set (GTEST_LIB_DIR ${GTEST_DIR}/lib/.libs)
set (GTEST_LIBS gtest gtest_main)
set (GMOCK_LIBS ${GTEST_LIBS} gmock gmock_main)

SET(zigbeeSrcTest  main.cpp
        ZCLTypeTest.cpp
        ZCLTypeTest.h)

file (GLOB zigbee_header  "../zigbee/*.h")

include_directories( .  ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})

add_executable(zigbeeLibTest  ${zigbeeSrcTest} )

target_link_libraries(zigbeeLibTest ${GMOCK_LIBS} pthread)
