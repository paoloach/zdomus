cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_subdirectory(JSZAttributes)
add_subdirectory(Exceptions)

add_library(javascript_lib STATIC
        $<TARGET_OBJECTS:jsZattributes_lib>
        $<TARGET_OBJECTS:js_exception_lib>
        JSObjects.h
        JavaScriptData.cpp
        JavaScriptExecuter.cpp
        JSDbManager.cpp
        JSDBTable.cpp
        JSLog.cpp
        JSManager.cpp
        JSRestServer.cpp
        JSRow.cpp
        JSZAttribute.cpp
        JSZAttributeFactory.cpp
        JSZCluster.cpp
        JSZDevice.cpp
        JSZDevices.cpp
        JSZEndpoint.cpp
        V8anyConverter.cpp
        V8Allocator.cpp
        V8Allocator.h
        JSZEndpoints.cpp JSZEndpoints.h
        GlobalJSFunctions.cpp GlobalJSFunctions.h
        JSCallbackFifo.cpp JSCallbackFifo.h
        JSResultSet.cpp JSResultSet.h
        JSRestParam.cpp JSRestParam.h JSBase.h)

target_include_directories(javascript_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR}  )
