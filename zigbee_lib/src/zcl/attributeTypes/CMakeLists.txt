cmake_minimum_required(VERSION 2.8)
project(zcl_attribute)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

SET(SOURCE_FILES
        ZCLbitmap8bitAttribute.cpp
        ZCLbooleanAttribute.cpp
        ZCLenum8bitAttribute.cpp
        ZCLIEEEAddressAttribute.cpp
        ZCLint16Attribute.cpp
        ZCLstringAttribute.cpp
        ZCLuint8Attribute.cpp
        ZCLuint16Attribute.cpp
        ZCLuint24Attribute.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(ZCL_Attribute OBJECT ${SOURCE_FILES} )