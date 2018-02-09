cmake_minimum_required(VERSION 3.7)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project(domus_engine)

set(CMAKE_CXX_STANDARD 17)

ExternalProject_Add(pistache_fork
        GIT_REPOSITORY https://github.com/paoloach/pistache.git
        GIT_SUBMODULES
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/pistache
        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs
        UPDATE_COMMAND "" # Skip annoying updates for every build
        INSTALL_COMMAND ""
        CMAKE_ARGS -DCMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        ${USE_PROJECT_CMAKE_MODULE_PATH}
        )


ExternalProject_Get_property(pistache_fork BINARY_DIR)
ExternalProject_Get_property(pistache_fork SOURCE_DIR)

set(PISTACHE_INCLUDE_DIR ${SOURCE_DIR}/include )
set(PISTACHE_LIB ${BINARY_DIR}/src/libpistache.a)


#ExternalProject_Add(trompeloeil
#        GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
#        GIT_SUBMODULES
#        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/trompeloeil
#        INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs
#        UPDATE_COMMAND "" # Skip annoying updates for every build
#        INSTALL_COMMAND ""
#        CMAKE_ARGS -DCMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH}
#        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
#        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
#        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
#        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
#        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#        ${USE_PROJECT_CMAKE_MODULE_PATH}
#        )



set(V8_DIR ${CMAKE_CURRENT_SOURCE_DIR}/v8)
set(V8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/v8/include ${PISTACHE_INCLUDE_DIR})

message("processor ${CMAKE_SYSTEM_PROCESSOR}")
message("V8_DIR ${V8_DIR}")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V8_LIB_DIR ${V8_DIR}/lib_x64.debug)
    message("V8_LIB_DIR ${V8_LIB_DIR}")
    set(V8_LIBRARY
            ${V8_LIB_DIR}/libv8_libplatform.so
            ${V8_LIB_DIR}/libv8_libbase.so
            ${V8_LIB_DIR}/libicui18n.so
            ${V8_LIB_DIR}/libicuuc.so
            ${V8_LIB_DIR}/libv8.so
            )
else ()
    if (BUILD_V8_VERSION MATCHES "arm")
        message("Using v8 ARM version")
        set(Boost_USE_STATIC_LIBS ON)
        set(V8_LIB_DIR ${V8_DIR}/lib_arm.release)
        set(V8_LIBRARY
                ${V8_LIB_DIR}/libv8_base.a
                ${V8_LIB_DIR}/libv8_external_snapshot.a
                ${V8_LIB_DIR}/libv8_libplatform.a
                ${V8_LIB_DIR}/libv8_libbase.a
                ${V8_LIB_DIR}/libv8_libsampler.a
                ${V8_LIB_DIR}/libicui18n.a
                ${V8_LIB_DIR}/libicuuc.a
                )
    else ()
        message("Using v8 x64 version")
        set(V8_LIB_DIR ${V8_DIR}/lib_x64.release)
        set(V8_LIBRARY
                ${V8_LIB_DIR}/libv8_libplatform.a
                ${V8_LIB_DIR}/libv8_libbase.a
                ${V8_LIB_DIR}/libicui18n.a
                ${V8_LIB_DIR}/libicuuc.a
                ${V8_LIB_DIR}/libv8.a
                )
    endif ()
endif ()

message("root path ${CMAKE_SYSROOT}")

set(ZIGBEE_LIB_DIR ${CMAKE_SYSROOT}/usr/local/zigbee)
set(ZIGBEELIB_INCLUDE_DIR ${ZIGBEE_LIB_DIR}/include)
set(ZIGBEELIB_LIB_DIR ${ZIGBEE_LIB_DIR}/lib)

set(LIBUSB_INCLUDE_DIR ${CMAKE_FIND_ROOT_PATH}/usr/include/libusb-1.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -g3 -O3 -Wall -Wextra -Wpedantic  -fno-omit-frame-pointer ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g2 -O3  -Wall -Wextra -Wpedantic -DBOOST_ALL_DYN_LINK  -fno-omit-frame-pointer ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g2 -O0  -Wall -Wextra -Wpedantic -DBOOST_ALL_DYN_LINK    -fno-omit-frame-pointer  ")

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)

find_package(Boost 1.63 COMPONENTS date_time fiber context system signals program_options filesystem log REQUIRED)

link_directories(${ZIGBEELIB_LIB_DIR} ${V8_LIB_DIR})


add_subdirectory(googletest/googlemock)
add_subdirectory(src/test)
add_subdirectory(src/serialDriver2)
add_subdirectory(src/DemoDriver)
add_subdirectory(src/usb)
add_subdirectory(src/Database)
add_subdirectory(src/ZigbeeData)
add_subdirectory(src/httpServer)
add_subdirectory(src/serialDriver)
add_subdirectory(src/Exception)
add_subdirectory(src/Utils)
add_subdirectory(src/JavaScript)
add_subdirectory(src/IO)
add_subdirectory(src/Configuration)
add_subdirectory(src/json)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if (CMAKE_C_COMPILER MATCHES "arm")
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-debug/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-debug/snapshot_blob.cpp)
    else ()
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-debug/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-debug/snapshot_blob.cpp)
    endif ()
else ()
    if (CMAKE_C_COMPILER MATCHES "arm")
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-release/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/arm-release/snapshot_blob.cpp )
    else ()
        set(V8_BLOB
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/native_blob.cpp
                ${CMAKE_SOURCE_DIR}/src/v8_blob/x64-release/snapshot_blob.cpp  src/usb/messages/zigbeeConfig.h)
    endif ()
endif ()


add_library(domus_engine_static_lib STATIC )

target_link_libraries(domus_engine_static_lib
        http_lib
        utils_lib
        zigbee_data_lib
        configuration_lib
        javascript_lib
        database_lib
        json_lib
        io_lib
        Boost::log
        Boost::log_setup)

target_include_directories(domus_engine_static_lib PUBLIC  Boost::bost)


add_executable(domus_engine
        src/main.cpp
        ${V8_BLOB}
        src/DemoDriver/DemoDriverFactory.h
        src/usb/UsbDriverFactory.h
        )

add_dependencies(domus_engine pistache_fork)

target_link_libraries(domus_engine
        domus_engine_static_lib
        serial2_driver_lib
        serial_driver_lib
        usb_driver_lib
        demo_driver_lib
        Boost::program_options
        Boost::thread
        )

set_property(TARGET domus_engine_static_lib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build/.lib)
set_property(TARGET domus_engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)

