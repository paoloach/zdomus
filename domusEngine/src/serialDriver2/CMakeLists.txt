cmake_minimum_required(VERSION 3.7)

project(domus_engine)

SET(SRC_SERIAL_DRIVER2
        Serial2DriverFactory.h
        SerialDriver2.cpp SerialDriver2.h
        Serial2ResponseExecutor.cpp Serial2ResponseExecutor.h
        IEEEAddressResponseErrorSerial2Executor.h
        IEEEAddressResponseSerial2Executor.h
        AnnunceSerial2Executor.h
        SimpleDescSerial2Executor.h SimpleDescSerial2Executor.cpp
        Serial2Executor.h
        ActiveEndpointSerial2ErrorExecutor.h
        BindTableSerial2Executer.h
        DeviceInfoSerial2Executor.h
        ReadAttributeResponseErrorSerial2.h
        ReadAttributeResponseSerial2.h ReadAttributeResponseSerial2.cpp
        AliveMessage2.h
        InvalidResponseSerial2Executor.h
        PowerNodeResponse2.cpp PowerNodeResponse2.h
        PowerNodeResponse2Error.cpp PowerNodeResponse2Error.h
        ReadThread.cpp ReadThread.h
        Packet.h
        AnnunceSerial2Executor.cpp
        AliveMessage2.cpp
        StringExecutor.cpp StringExecutor.h
        PacketSend.h
        DeviceInfoSerial2Executor.cpp
        IEEEAddressResponseSerial2Executor.cpp
        NodeDescriptionResponse2.cpp NodeDescriptionResponse2.h
        NodeDescriptionResponseError2.cpp NodeDescriptionResponseError2.h)


add_library(serial2_driver_lib OBJECT ${SRC_SERIAL_DRIVER2} )

target_include_directories( serial2_driver_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} )