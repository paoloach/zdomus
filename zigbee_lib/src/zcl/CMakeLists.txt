cmake_minimum_required(VERSION 2.8)
project(zcl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

SET(SOURCE_FILES
        Cluster.cpp
        ClusterTypeFactory.cpp
        OnOffLight.cpp
        ZCLAttribute.cpp
        ZCLDevice.cpp)

add_subdirectory(attributeTypes)
add_subdirectory(clusterTypes)

add_library(ZCL OBJECT  ${SOURCE_FILES}  )

#add_dependencies(ZCL ZCL_Attribute ZCL_Clusters)

include_directories(${CMAKE_SOURCE_DIR}/src)

