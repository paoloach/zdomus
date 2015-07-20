Library that containt base objects in order to interact with zigbee in a more object oriented style

It contains also a driver class in order to connect with a usb dongle to comunicate with zigbee  devices

To compile this librery it's need a cx14 compiler (for example gcc >= 4.9) 
It use libboost, libusb and google mock for tests

Differently from suggest by google mock, this library is expected to be installed (for example in /usr/local). The header files are supposed to by into gmock/gmock.h and gtest/gtest.h while le libraries into a path as /usr/local/lib or /usr/lib

To compile:
cmake .

make

to install

make install