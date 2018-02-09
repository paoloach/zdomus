cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_subdirectory(RestActions)

SET(SRC_HTTP
        RestHandler.h
        RestHandlerImpl.cpp RestHandlerImpl.h
        ApplicationJSONProducer.cpp ApplicationJSONProducer.h
        MediaTypeProducer.h
        MediaTypeProducerFactory.cpp MediaTypeProducerFactory.h
        PlainTextProducer.cpp PlainTextProducer.h
        $<TARGET_OBJECTS:rest_actions_lib>
        )



add_library(http_lib STATIC ${SRC_HTTP} )
target_include_directories(http_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR} )
target_link_libraries(http_lib PUBLIC ${PISTACHE_LIB})
