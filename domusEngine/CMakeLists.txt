cmake_minimum_required (VERSION 2.6)
project (domus_engine)

set(CMAKE_BUILD_TYPE Debug)

set (GMOCK_DIR /home/paolo/workspace_luna/gmock-1.7.0)
set (GTEST_DIR /home/paolo/workspace_luna/gmock-1.7.0/gtest)
set (GMOCK_INCLUDE_DIR ${GMOCK_DIR}/include)
set (GTEST_INCLUDE_DIR ${GTEST_DIR}/include)
set (GMOCK_LIB_DIR ${GMOCK_DIR}/lib/.libs)
set (GTEST_LIB_DIR ${GTEST_DIR}/lib/.libs)
set (GTEST_LIBS gtest gtest_main)
set (GMOCK_LIBS ${GTEST_LIBS} gmock gmock_main)


set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g3 -O2 -std=c++14 ")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g3 -O0  -std=c++14 -Wall -Wextra -Wpedantic ")

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)


find_package(Boost  COMPONENTS system thread signals program_options filesystem REQUIRED)

link_directories( /usr/local/zigbee/lib /usr/local/v8 ${GMOCK_LIB_DIR} ${GTEST_LIB_DIR})

include_directories(/usr/include/libusb-1.0 /usr/local/zigbee/include /usr/local/v8 /usr/local/v8/include ./include ${GMOCK_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} /usr/include/postgresql/server )


file (GLOB src  "src/*.cpp")
file (GLOB srcUsb  "src/usb/*.cpp")
file (GLOB srcZigbeeData  "src/ZigbeeData/*.cpp")
file (GLOB srcZigbeeDataPT  "src/ZigbeeData/PropertyTree/*.cpp")
file (GLOB srcZigbeeDataExceptions  "src/ZigbeeData/Exceptions/*.cpp")
file (GLOB srcComand  "src/Comand/*.cpp")
file (GLOB srcIO  "src/IO/*.cpp")
file (GLOB srcUtils  "src/Utils/*.cpp")
file (GLOB srcDatabase  "src/Database/*.cpp")
file (GLOB srcDatabase_exceptions  "src/Database/Exceptions/*.cpp")
file (GLOB srcConfiguration  "src/Configuration/*.cpp")
file (GLOB srcJavaScript_attributes  "src/JavaScript/JSZAttributes/*.cpp")
file (GLOB srcJavaScript_exceptions  "src/JavaScript/Exceptions/*.cpp")
file (GLOB srcJavaScript  "src/JavaScript/*.cpp")
file (GLOB srcHttpServer "src/httpServer/*.cpp")
file (GLOB srcRestParser "src/httpServer/RestParser/*.cpp")
file (GLOB srcRestActions "src/httpServer/RestActions/*.cpp")

file (GLOB test  "src/test/*.cpp")
file (GLOB testZigbeeData  "src/test/ZigbeeData/*.cpp")
file (GLOB testIO  "src/test/IO/*.cpp")
file (GLOB testUtils  "src/test/Utils/*.cpp")
file (GLOB testMocks  "src/test/Mocks/*.cpp")
file (GLOB testMocksHttp  "src/test/Mocks/http/*.cpp")
file (GLOB testComand  "src/test/Comand/*.cpp")
file (GLOB testConfiguration  "src/test/Configuration/*.cpp")
file (GLOB testDatabase  "src/test/Database/*.cpp")
file (GLOB testJavascript  "src/test/Javascript/*.cpp")
file (GLOB testJavascriptAttributes  "src/test/Javascript/JSAttributes/*.cpp" )
file (GLOB testHttpServer "src/test/httpServer/*.cpp")
file (GLOB testRestParser "src/test/httpServer/RestParser/*.cpp")

find_library(libplatform libv8_libplatform.a)

#set (V8_LIBRARY_PATH /usr/local/v8/lib_debug/)
set (V8_LIBRARY_PATH /usr/local/v8/lib/)
set (V8_LIBRARY 
	${V8_LIBRARY_PATH}libv8_libplatform.a
	${V8_LIBRARY_PATH}libv8_base.a
	${V8_LIBRARY_PATH}libv8_libbase.a
	${V8_LIBRARY_PATH}libv8_snapshot.a
	${V8_LIBRARY_PATH}libicui18n.a
	${V8_LIBRARY_PATH}libicuuc.a
	${V8_LIBRARY_PATH}libicudata.a
	)
	
add_library(domus_engine_static_lib STATIC 
	${srcUsb} 
	${srcZigbeeData}
	${srcZigbeeDataPT}
	${srcIO}
	${srcUtils}
	${srcComand}
	${srcJavaScript}
	${srcConfiguration} 
	${srcZigbeeDataExceptions} 
	${srcJavaScript_attributes}
	${srcJavaScript_exceptions}
	${srcDatabase}
	${srcDatabase_exceptions}
	${srcHttpServer}
	${srcRestParser}
	${srcRestActions}
	)
add_executable(domus_engine  src/main.cpp )
add_executable(domus_engine_test 
				 src/test/main.cpp 
				 ${testJavascript}
				 ${testZigbeeData}
				 ${testIO}
				 ${testUtils}
				 ${testMocks}
				 ${testComand}
				 ${testDatabase}
				 ${testConfiguration}
				 ${testJavascriptAttributes}
				 ${testHttpServer}
				 ${testMocksHttp}
				 ${testRestParser}
				 )    
    

SET (LIBS 	zigbeeLib
	usb-1.0
	pq
	PocoNetd
	PocoUtild
	PocoXMLd
	PocoZipd
	PocoDatad
	PocoFoundationd
	${V8_LIBRARY}
	${Boost_SIGNALS_LIBRARY_DEBUG}
	${Boost_THREAD_LIBRARY_RELEASE}
	${Boost_SYSTEM_LIBRARY_RELEASE}
	${Boost_FILESYSTEM_LIBRARY_RELEASE}
	${Boost_PROGRAM_OPTIONS_LIBRARY_DEBUG}
	
	pthread
)
   
target_link_libraries(domus_engine domus_engine_static_lib ${V8_LIBRARY} ${LIBS} )
target_link_libraries(domus_engine_test domus_engine_static_lib ${V8_LIBRARY} ${LIBS}  ${GMOCK_LIBS})
    

set_property(TARGET domus_engine_static_lib PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build/.lib)   
set_property(TARGET domus_engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)
set_property(TARGET domus_engine_test PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)
