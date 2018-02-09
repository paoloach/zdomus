cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_library(configuration_lib STATIC
        Configuration.cpp Configuration.h
        )


target_include_directories(configuration_lib PUBLIC  ${CMAKE_SOURCE_DIR}/include )
