cmake_minimum_required(VERSION 3.7)

project(domus_engine)

SET(SRC_DEMO_DRIVER  DemoDevice.cpp DemoDevice.h)

add_library(demo_driver_lib STATIC ${SRC_DEMO_DRIVER} )
target_include_directories(demo_driver_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR} )
target_link_libraries(demo_driver_lib PUBLIC  Boost::fiber)