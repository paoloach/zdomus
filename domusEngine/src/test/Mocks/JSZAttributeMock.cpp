/*
 * JSZAttributeMock.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeMock.h"


namespace zigbee {
    namespace test {
        static JSCallbackFifo fifo;
        JSZAttributeMock::JSZAttributeMock() : JSZAttribute(nullptr, fifo, ZCLTypeDataType::ZCLTypeInvalid) {

        }

        JSZAttributeMock::~JSZAttributeMock() {
        }

    } /* namespace test */
} /* namespace zigbee */