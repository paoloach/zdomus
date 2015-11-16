cmake_minimum_required(VERSION 2.8)
project(zcl_cluster_type)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC")

SET(SOURCE_FILES
        BasicCluster.cpp
        DeviceTemperatureConfiguration.cpp
        FlowMeasurementCluster.cpp
        GroupsCluster.cpp
        IdentifyCluster.cpp
        IlluminanceLevelSensingCluster.cpp
        IlluminanceMeasurementCluster.cpp
        LevelControlCluster.cpp
        MeteringCluster.cpp
        NullCluster.cpp
        OccupancySensingCluster.cpp
        OnOffCluster.cpp
        PowerConfigurationCluster.cpp
        PressureMeasurementCluster.cpp
        RelativeHumidityMeasuramentCluster.cpp
        ScenesCluster.cpp
        TemperatureMeasurementCluster.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(ZCL_Clusters OBJECT  ${SOURCE_FILES}  )