cmake_minimum_required(VERSION 3.7)

project(domus_engine)

set(SRC_UTILS
        AttributeWriterResult.cpp AttributeWriterResult.h
        AttributeWriter.cpp AttributeWriter.h
        Clusters.cpp Clusters.h
        SingletonObjects.h SingletonObjectsImpl.cpp SingletonObjectsImpl.h
        DeviceInfoDispatcher.cpp DeviceInfoDispatcher.h
        Constant.cpp Constant.h
        LogConstants.h
        DriverFactory.h
        )

add_library(utils_lib STATIC ${SRC_UTILS}  )
target_include_directories(utils_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR}  ${PISTACHE_INCLUDE_DIR} ${V8_INCLUDE_DIR})
target_link_libraries(utils_lib PUBLIC zigbeeLib)
