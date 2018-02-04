cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_library(jsZattributes_lib OBJECT
        JSZAttributeTemplate.h
        ParamBool.h
        ParamCheckNull.h
        ParamIEEEAddress.h
        ParamInt32.h
        ParaUInt32.h
        ParamString.h
        )

target_include_directories(jsZattributes_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} )
