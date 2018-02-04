cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_library(json_lib OBJECT
        jsoncpp.cpp
        json/json-forwards.h
        json/json.h)
