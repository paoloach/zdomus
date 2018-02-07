cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_library(io_lib OBJECT
        DataPropertyTree.cpp DataPropertyTree.h
        ProperyTreeUtils.cpp ProperyTreeUtils.h)

target_include_directories(io_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

