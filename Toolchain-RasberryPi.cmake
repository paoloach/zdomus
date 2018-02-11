# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

SET(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSROOT /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot)
set(CMAKE_STAGING_PREFIX /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot/usr/local)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/bin/armv6-unknown-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/bin/armv6-unknown-linux-gnueabihf-g++)


SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(BUILD_V8_VERSION  arm)

#include_directories( /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot/include)
