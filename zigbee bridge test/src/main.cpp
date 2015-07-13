/*
 * main.cpp
 *
 *  Created on: 06/lug/2014
 *      Author: paolo
 */

#include <QtGui/QApplication>
#include <libusb.h>
#include <iostream>

#include "MainWindow.h"

using zigbee::MainWindow;
using namespace std;

int main(int argc, char *argv[])
{

	libusb_context * usbContext=NULL;
	if (libusb_init(&usbContext) != 0){
		cerr << "Unable to initialize the libusb" << endl;
		return -1;
	}

    QApplication app(argc, argv);
    app.setOrganizationName("QtProject");
    app.setApplicationName("Application Example");
    MainWindow mainWin(usbContext);
    mainWin.show();
    app.exec();
    libusb_exit(usbContext);
}


