cmake_minimum_required(VERSION 3.7)

project(domus_engine)

set(USB_SRC ActiveEPReqError.h
        AnnunceMsgExecuter.h
        AttributeValueReqError.cpp
        AttributeValueReqError.h
        AttributeValuesExecuter.h
        BindResponse.cpp
        BindResponse.h
        BindTableExecuter.h
        Executor.h
        RequestedAttributes.cpp
        RequestedAttributes.h
        SimpleDescExecutor.h
        usbConfig.h
        USBDevice.cpp
        USBDevice.h
        UsbResponseExecutors.cpp
        UsbResponseExecutors.h
        InfoMessageExecuter.h DeviceInfoExecutor.cpp
        DeviceInfoExecutor.h
        IEEEAddressResponseExecutor.h
        PowerNodeReqError.h
        messages/PowerNodeRequestMessage.h
        messages/PowerNodeRespMessage.h UsbDriverFactory.cpp)


add_library(usb_driver_lib STATIC ${USB_SRC} )
target_include_directories(usb_driver_lib PUBLIC ${ZIGBEELIB_INCLUDE_DIR} ${LIBUSB_INCLUDE_DIR} )
target_link_libraries(usb_driver_lib PUBLIC  usb-1.0 Boost::fiber)
