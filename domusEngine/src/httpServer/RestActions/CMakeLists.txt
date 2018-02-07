cmake_minimum_required(VERSION 3.7)

project(domus_engine)

SET(SRC_REST_ACTIONS
        ClusterThrowingException.cpp ClusterThrowingException.h
        DeleteDevice.cpp DeleteDevice.h
        ExecuteBind.cpp ExecuteBind.h
        ExecuteCmd.cpp ExecuteCmd.h
        ExecuteReset.cpp ExecuteReset.h
        ShowPowerNode.cpp ShowPowerNode.h
        GetChildren.cpp GetChildren.h
        GetChildren.cpp GetChildren.h
        getNodeDescription.cpp getNodeDescription.h
        ShowAttribute.cpp ShowAttribute.h
        ShowAttributeFactory.cpp ShowAttributeFactory.h
        ShowBindTable.cpp ShowBindTable.h
        ShowDevice.cpp ShowDevice.h
        ShowDeviceInfo.cpp ShowDeviceInfo.h
        ShowDevices.cpp ShowDevices.cpp
        ShowEndpoint.cpp ShowEndpoint.h
        ShowHello.cpp ShowHello.cpp
        ShowInCluster.cpp ShowInCluster.h
        ShowOutCluster.cpp ShowOutCluster.h
        ShowPowerNode.cpp ShowPowerNode.h
        ShowTopology.cpp ShowTopology.h
        ShowWhoAreYou.cpp ShowWhoAreYou.h
        UpdateAttributes.cpp UpdateAttributes.h
        )


add_library(rest_actions_lib OBJECT ${SRC_REST_ACTIONS} )
target_include_directories(rest_actions_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/include ${PISTACHE_INCLUDE_DIR})
