cmake_minimum_required(VERSION 3.7)

project(domus_engine)

SET(SRC_DEMO_DRIVER  DemoDevice.cpp DemoDevice.h)

include_directories( ${ZIGBEELIB_INCLUDE_DIR})

add_library(demo_driver_lib OBJECT ${SRC_DEMO_DRIVER} )