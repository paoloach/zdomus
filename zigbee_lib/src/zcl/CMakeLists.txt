cmake_minimum_required(VERSION 2.8)
project(zcl)

SET(SOURCE_FILES
        Cluster.cpp
        ClusterTypeFactory.cpp
        OnOffLight.cpp
        ZCLAttribute.cpp
        ZCLDevice.cpp)

add_subdirectory(attributeTypes)
add_subdirectory(clusterTypes)

add_library(ZCL STATIC SHARED  ${SOURCE_FILES} )

add_dependencies(ZCL ZCL_Attribute ZCL_Clusters)

target_link_libraries(ZCL zcl_attribute ZCL_Clusters)