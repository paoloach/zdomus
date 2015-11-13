cmake_minimum_required(VERSION 2.8)
project(zcl_cluster_type)

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

add_library(ZCL_Clusters STATIC SHARED  ${SOURCE_FILES} )