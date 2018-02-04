cmake_minimum_required(VERSION 3.7)

project(domus_engine)

add_library(js_exception_lib OBJECT
        JSException.cpp JSException.h
        JSExceptionArgNoBool.cpp JSExceptionArgNoBool.h
        JSExceptionArgNoExtAddress.cpp JSExceptionArgNoExtAddress.h
        JSExceptionArgNoFunction.cpp JSExceptionArgNoFunction.h
        JSExceptionArgNoIEEEAddress.cpp JSExceptionArgNoIEEEAddress.h
        JSExceptionArgNoInteger.cpp JSExceptionArgNoInteger.h
        JSExceptionArgNoString.cpp JSExceptionArgNoString.h
        JSExceptionArgNoUInteger.cpp JSExceptionArgNoUInteger.h
        JSExceptionInvalidAttributeType.cpp JSExceptionInvalidAttributeType.h
        JSExceptionNoAttribute.cpp JSExceptionNoAttribute.h
        JSExceptionNoDevice.cpp JSExceptionNoDevice.h
        JSExceptionNoEndpoint.cpp JSExceptionNoEndpoint.h
        JSExceptionNoInCluster.cpp JSExceptionNoInCluster.h
        JSExceptionOnlyOneArgument.cpp JSExceptionOnlyOneArgument.h
        JSExceptionOnlyTwoArguments.cpp JSExceptionOnlyTwoArguments.h
        JSExceptionOutOfRange.cpp JSExceptionOutOfRange.cpp
        JSExceptionStream.cpp JSExceptionStream.h
        JSExceptionWrongArgumentsNumber.cpp          JSExceptionWrongArgumentsNumber.h
        )

target_include_directories(js_exception_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} )
