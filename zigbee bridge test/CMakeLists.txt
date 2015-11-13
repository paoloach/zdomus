cmake_minimum_required(VERSION 3.3)
project(zigbee_bridge_test)

find_package(Qt4)
find_package(KDE4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fexceptions " )

set(SOURCE_FILES
    src/AttributeHandler/AttributeChanger.cpp
    src/AttributeHandler/Bitmap8BitChanger.cpp
    src/AttributeHandler/BoolAttributeChanger.cpp
    src/AttributeHandler/Enum8BitChanger.cpp
    src/AttributeHandler/Int16Changer.cpp
    src/AttributeHandler/StringAttributeChanger.cpp
    src/AttributeHandler/UInt16Changer.cpp
    src/AttributeHandler/UInt24Changer.cpp
    src/AttributeHandler/UInt8Changer.cpp
    src/TreeWidgetItem/QTreeBindTableDest.cpp
    src/TreeWidgetItem/QTreeBindTableSrc.cpp
    src/TreeWidgetItem/TreeWidgetCluster.cpp
    src/TreeWidgetItem/TreeWidgetDevice.cpp
    src/ui/InsertCmdParams.cpp
    src/ui/moc_InsertCmdParams.cxx
    src/ui/ParamIEEEAddress.cpp
    src/ui/ParamList.cpp
    src/ui/ParamString.cpp
    src/ui/ParamUInteger.cpp
    src/AttributeHandler.cpp
    src/ClustersHandler.cpp
    src/ClustersOutHandler.cpp
    src/ClusterTreeHandler.cpp
    src/ExtAddress.cpp
    src/main.cpp
    src/MainWindow.cpp
    src/QTreeDeviceItem.cpp
    src/QTreeWidgetEndpoint.cpp
    src/TreeItemSignalMap.cpp)

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

file (GLOB ui  "src/ui/*.ui")

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

add_executable(zigbee_bridge ${SOURCE_FILES} ${UI_HEADERS} ${QOBJECT_MOC} )


target_link_libraries(zigbee_bridge
        zigbeeLib
        ${QT_QTCORE_LIBRARY}
        ${QT_QTGUI_LIBRARY}
        kdeui
        usb-1.0
        )

set_property(TARGET zigbee_bridge PROPERTY RUNTIME_OUTPUT_DIRECTORY ./build)