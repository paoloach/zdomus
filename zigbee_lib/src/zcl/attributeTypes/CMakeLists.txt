cmake_minimum_required(VERSION 2.8)
project(zcl_attribute)

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

add_library(ZCL_Attribute STATIC SHARED  ${SOURCE_FILES} )