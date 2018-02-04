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


ExternalProject_Get_Property(pistache_fork install_dir)

set(PISTACHE_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/pistache/src/pistache_fork/include ${CMAKE_CURRENT_BINARY_DIR}/pistache/src/pistache_fork/include/pistache)
set(PISTACHE_LIB ${CMAKE_CURRENT_BINARY_DIR}/pistache/src/pistache_fork-build/src/libpistache.a)


set(V8_DIR ${CMAKE_BINARY_DIR}/v8)
set(V8_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/v8/include ${PISTACHE_INCLUDE_DIR})

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(V8_LIB_DIR ${V8_DIR}/lib_x64.debug)
    set(V8_LIBRARY
            v8_libplatform
            v8_libbase
            icui18n
            icuuc
            v8
            )
else ()
    if (BUILD_V8_VERSION MATCHES "arm")
        message("Using v8 ARM version")
        set(Boost_USE_STATIC_LIBS ON)
        set(V8_LIB_DIR ${V8_DIR}/lib_arm.release)
        set(V8_LIBRARY
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libicui18n.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libicuuc.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_base.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_external_snapshot.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_libbase.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_libplatform.a
                ${CMAKE_CURRENT_SOURCE_DIR}/v8/lib_arm.release/libv8_libsampler.a
                )
    else ()
        message("Using v8 x64 version")
        set(V8_LIB_DIR ${V8_DIR}/lib_x64.release)
        set(V8_LIBRARY
                v8_libplatform
                v8_libbase
                icui18n
                icuuc
                v8
                )
    endif ()
endif ()


set(ZIGBEE_LIB_DIR ${CMAKE_FIND_ROOT_PATH}/usr/local/zigbee)
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
include_directories(./include  ${ZIGBEELIB_INCLUDE_DIR} ${V8_INCLUDE_DIR})

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


add_library(domus_engine_static_lib STATIC
        $<TARGET_OBJECTS:utils_lib>
        $<TARGET_OBJECTS:http_lib>
        $<TARGET_OBJECTS:rest_actions_lib>
        $<TARGET_OBJECTS:io_lib>
        $<TARGET_OBJECTS:configuration_lib>
        $<TARGET_OBJECTS:exceptions_lib>
        $<TARGET_OBJECTS:json_lib>
        )


add_executable(domus_engine src/main.cpp ${V8_BLOB}
        src/DemoDriver/DemoDriverFactory.h
        src/usb/UsbDriverFactory.h
        $<TARGET_OBJECTS:demo_driver_lib>
        $<TARGET_OBJECTS:usb_driver_lib>
        $<TARGET_OBJECTS:serial2_driver_lib>
        $<TARGET_OBJECTS:serial_driver_lib>
          )

add_dependencies(domus_engine pistache_fork)

SET(LIBS zigbeeLib
        usb-1.0

        ${V8_LIBRARY}
        ${Boost_SIGNALS_LIBRARY_RELEASE}
        ${Boost_THREAD_LIBRARY_RELEASE}
        ${Boost_SYSTEM_LIBRARY_RELEASE}
        ${Boost_FILESYSTEM_LIBRARY_RELEASE}
        ${Boost_LOG_LIBRARY_RELEASE}
        ${Boost_LOG_SETUP_LIBRARY_RELEASE}
        ${Boost_CONTEXT_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY_RELEASE}
        ${Boost_FIBER_LIBRARY_RELEASE}
        ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE}
        ${PISTACHE_LIB}
        dl
        pthread
        )

target_link_libraries(domus_engine_static_lib javascript_lib zigbee_data_lib database_lib)
target_link_libraries(domus_engine domus_engine_static_lib ${V8_LIBRARY} ${LIBS}  )


set_property(TARGET domus_engine_static_lib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build/.lib)
set_property(TARGET domus_engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)

