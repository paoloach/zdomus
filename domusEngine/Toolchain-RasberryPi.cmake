# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /home/paolo/x-tools6h/arm-unknown-linux-gnueabihf/bin/arm-unknown-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /home/paolo/x-tools6h/arm-unknown-linux-gnueabihf/bin/arm-unknown-linux-gnueabihf-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /home/paolo/x-tools6h/arm-unknown-linux-gnueabihf/arm-unknown-linux-gnueabihf/sysroot)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set (GMOCK_LIB_DIR /usr/lib)
set (GTEST_LIB_DIR /usr/lib)

set (GTEST_LIBS gtest)
set (GMOCK_LIBS ${GTEST_LIBS} gmock)