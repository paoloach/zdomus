/*
 * JSZAttributeMock.cpp
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#include "JSZAttributeMock.h"


namespace zigbee {
    namespace test {

        JSZAttributeMock::JSZAttributeMock() : JSZAttribute(nullptr, ZCLTypeDataType::ZCLTypeInvalid) {

        }

        JSZAttributeMock::~JSZAttributeMock() {
        }

    } /* namespace test */
} /* namespace zigbee */