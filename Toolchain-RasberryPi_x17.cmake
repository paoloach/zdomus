# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/bin/armv6-unknown-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/bin/armv6-unknown-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot)
SET(CMAKE_INSTALL_PREFIX  ${CMAKE_FIND_ROOT_PATH}/usr/local)



# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(BUILD_V8_VERSION  arm)

include_directories( /opt/cross/x-tools/armv6-unknown-linux-gnueabihf/armv6-unknown-linux-gnueabihf/sysroot/include)
