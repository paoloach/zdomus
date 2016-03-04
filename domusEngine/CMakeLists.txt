cmake_minimum_required(VERSION 2.8)
project(domus_engine)

set(CMAKE_BUILD_TYPE Release)
add_subdirectory(googletest/googlemock)
add_subdirectory(src/test)

set(V8_DIR ${CMAKE_FIND_ROOT_PATH}/usr/local/v8)
set(V8_INCLUDE_DIR ${V8_DIR} ${V8_DIR}/include)
set(V8_LIB_DIR ${V8_DIR}/lib)
set(ZIGBEE_LIB_DIR ${CMAKE_FIND_ROOT_PATH}/usr/local/zigbee)
set(ZIGBEELIB_INCLUDE_DIR ${ZIGBEE_LIB_DIR}/include)
set(ZIGBEELIB_LIB_DIR ${ZIGBEE_LIB_DIR}/lib)

set(LIBUSB_INCLUDE_DIR ${CMAKE_FIND_ROOT_PATH}/usr/include/libusb-1.0)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -ggdb -O2 -std=c++14  -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -ggdb -O0  -std=c++14 -Wall -Wextra -Wpedantic ")

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)

find_package(PostgreSQL)
find_package(Boost COMPONENTS system thread signals program_options filesystem REQUIRED)

link_directories(${ZIGBEELIB_LIB_DIR} ${V8_LIB_DIR})
include_directories(./include ${LIBUSB_INCLUDE_DIR} ${PostgreSQL_INCLUDE_DIRS} ${ZIGBEELIB_INCLUDE_DIR} ${V8_INCLUDE_DIR})


file(GLOB src "src/*.cpp")
file(GLOB srcUsb "src/usb/*.cpp")
file(GLOB srcZigbeeData "src/ZigbeeData/*.cpp")
file(GLOB srcZigbeeDataPT "src/ZigbeeData/PropertyTree/*.cpp")
file(GLOB srcZigbeeDataExceptions "src/ZigbeeData/Exceptions/*.cpp")
file(GLOB srcComand "src/Comand/*.cpp")
file(GLOB srcIO "src/IO/*.cpp")
file(GLOB srcUtils "src/Utils/*.cpp")
file(GLOB srcDatabase "src/Database/*.cpp")
file(GLOB srcDatabase_exceptions "src/Database/Exceptions/*.cpp")
file(GLOB srcConfiguration "src/Configuration/*.cpp")
file(GLOB srcJavaScript_attributes "src/JavaScript/JSZAttributes/*.cpp")
file(GLOB srcJavaScript_exceptions "src/JavaScript/Exceptions/*.cpp")
file(GLOB srcHttpServer "src/httpServer/*.cpp")
file(GLOB srcRestParser "src/httpServer/RestParser/*.cpp")
file(GLOB srcRestActions "src/httpServer/RestActions/*.cpp")


set(V8_LIBRARY
        ${V8_LIB_DIR}/libv8_libplatform.a
        ${V8_LIB_DIR}/libv8_base.a
        ${V8_LIB_DIR}/libv8_libbase.a
        ${V8_LIB_DIR}/libv8_external_snapshot.a
        ${V8_LIB_DIR}/libv8_nosnapshot.a
        ${V8_LIB_DIR}/libicui18n.a
        ${V8_LIB_DIR}/libicuuc.a
        ${V8_LIB_DIR}/libicudata.a
        )

add_library(javascript_lib OBJECT
        src/JavaScript/JavaScriptData.cpp
        src/JavaScript/JavaScriptExecuter.cpp
        src/JavaScript/JSDbManager.cpp
        src/JavaScript/JSDBTable.cpp
        src/JavaScript/JSLog.cpp
        src/JavaScript/JSManager.cpp
        src/JavaScript/JSRestServer.cpp
        src/JavaScript/JSRow.cpp
        src/JavaScript/JSZAttribute.cpp
        src/JavaScript/JSZAttributeFactory.cpp
        src/JavaScript/JSZCluster.cpp
        src/JavaScript/JSZDevice.cpp
        src/JavaScript/JSZDevices.cpp
        src/JavaScript/JSZEndpoint.cpp
        src/JavaScript/V8anyConverter.cpp src/JavaScript/V8Allocator.cpp src/JavaScript/V8Allocator.h)

add_library(domus_engine_static_lib STATIC
        ${srcUsb}
        ${srcZigbeeData}
        ${srcZigbeeDataPT}
        ${srcIO}
        ${srcUtils}
        ${srcComand}
        #	${srcJavaScript}
        ${srcConfiguration}
        ${srcZigbeeDataExceptions}
        ${srcJavaScript_attributes}
        ${srcJavaScript_exceptions}
        ${srcDatabase}
        ${srcDatabase_exceptions}
        ${srcHttpServer}
        ${srcRestParser}
        ${srcRestActions}
        $<TARGET_OBJECTS:javascript_lib>
        )
add_executable(domus_engine src/main.cpp)


SET(LIBS zigbeeLib
        usb-1.0
        pq
        PocoNet
        PocoUtil
        PocoXML
   #con     PocoZip
   #     PocoData
        PocoFoundation
        ${V8_LIBRARY}
        ${Boost_SIGNALS_LIBRARY_DEBUG}
        ${Boost_THREAD_LIBRARY_RELEASE}
        ${Boost_SYSTEM_LIBRARY_RELEASE}
        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
        ${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG}
        dl
        pthread
        )

target_link_libraries(domus_engine domus_engine_static_lib ${V8_LIBRARY} ${LIBS})


set_property(TARGET domus_engine_static_lib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build/.lib)
set_property(TARGET domus_engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)

