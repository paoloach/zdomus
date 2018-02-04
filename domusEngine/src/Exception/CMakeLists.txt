cmake_minimum_required(VERSION 3.7)

project(domus_engine)

SET(SRC_EXCEPTION
        PathNotFound.h
        Timeout.h)

add_library(exceptions_lib OBJECT ${SRC_EXCEPTION} )
target_include_directories(exceptions_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} )
