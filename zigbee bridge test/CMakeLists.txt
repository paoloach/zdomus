cmake_minimum_required (VERSION 2.6)
project (zigbee_bridge_test)

set(CMAKE_BUILD_TYPE Release)

add_custom_target(debug cmake -DCMAKE_BUILD_TYPE=Debug COMMAND make)
add_custom_target(release cmake -DCMAKE_BUILD_TYPE=Release COMMAND make)


set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -pipe -g3 -O0 -std=c++14")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pipe  -g3 -O0  -std=c++14")

#find_package(Boost 1.42 COMPONENTS system filesystem thread date_time regex REQUIRED)
find_package(Qt4 4.8.1)

file (GLOB src  "src/*.cpp")
file (GLOB zcl_src  "src/zcl/*.cpp")
file (GLOB zigbee_src  "src/zigbee/*.cpp")
file (GLOB attributeTypes_src  "src/zcl/attributeTypes/*.cpp")
file (GLOB clusterTypes_src  "src/zcl/clusterTypes/*.cpp")
file (GLOB clusterHandlerAttributes_src  "src/clusterHandler/AttributeHandler/*.cpp")
file (GLOB uiSrc "src/ui/*.cpp")
file (GLOB ui  "src/ui/*.ui")
file (GLOB attributeHandler  "src/AttributeHandler/*.cpp")
file (GLOB treeWidgetItems  "src/TreeWidgetItem/*.cpp")
set  (QOBJECT_FILES 
	  src/MainWindow.h
	  src/ClusterTreeHandler.h
	  src/AttributeHandler.h
	  src/AttributeHandler/BoolAttributeChanger.h
	  src/AttributeHandler/StringAttributeChanger.h
	  src/AttributeHandler/Bitmap8BitChanger.h
	  src/AttributeHandler/UInt8Changer.h
	  src/AttributeHandler/UInt16Changer.h
	  src/AttributeHandler/UInt24Changer.h
	  src/AttributeHandler/Int16Changer.h
	  src/AttributeHandler/Enum8BitChanger.h
	  src/ui/InsertCmdParams.h
	  )

QT4_WRAP_UI(UI_HEADERS  ${ui})
QT4_WRAP_CPP(QOBJECT_MOC ${QOBJECT_FILES})

link_directories(${QT_LIBRARY_DIR} /usr/local/zigbee/lib)
include_directories(${QT_HEADERS_DIR} /usr/include/libusb-1.0 /usr/local/zigbee/include)

add_executable(zigbee_bridge  ${src} ${clusterHandler_src} ${clusterHandlerAttributes_src}  ${attributeHandler} ${UI_HEADERS} ${QOBJECT_MOC} ${uiSrc} ${treeWidgetItems} )
    
    
target_link_libraries(zigbee_bridge 
	zigbeeLib
	${QT_QTCORE_LIBRARY}
	${QT_QTGUI_LIBRARY}
	kdeui
	usb-1.0
    )
  
set_property(TARGET zigbee_bridge PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)


