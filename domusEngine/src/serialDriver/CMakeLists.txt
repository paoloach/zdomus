cmake_minimum_required(VERSION 3.7)

project(domus_engine)

SET(SRC_SERIAL_DRIVER
        SerialDriver.cpp SerialDriver.h
        InvalidResponseSerialExecutor.h
        IEEEAddressResponseErrorSerialExecutor.h AnnunceSerialExecutor.h
        SerialResponseExecutor.cpp SerialResponseExecutor.h
        SerialExecutor.h
        IEEEAddressResponseSerialExecutor.h
        SimpleDescSerialExecutor.h
        ActiveEndpointErrorExecutor.h
        BindTableSerialExecuter.h
        ReadAttributeResponseErrorSerial.h
        PowerNodeResponseError.cpp PowerNodeResponseError.h
        ReadAttributeResponseSerial.h
        DeviceInfoSerialExecutor.h
        PowerNodeResponse.cpp PowerNodeResponse.h
        AliveMessage.h
        AnnunceSerialExecutor.cpp
        IEEEAddressResponseSerialExecutor.cpp)

add_library(serial_driver_lib OBJECT ${SRC_SERIAL_DRIVER} )
target_include_directories(serial_driver_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} )
