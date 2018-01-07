/*
 * ZCLbitmap8bitAttributeMock.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZCLBITMAP8BITATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_ZCLBITMAP8BITATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

#include <zcl/attributeTypes/ZCLbitmap8bitAttribute.h>

namespace zigbee {
    namespace test {

        class ZCL_bitmap8bit_AttributeMock : public ZCLBitmap8bitAttribute {
        public:
            ZCL_bitmap8bit_AttributeMock();

            virtual ~ZCL_bitmap8bit_AttributeMock();

            MAKE_MOCK0(sendValue, void (uint8_t ), override);

            MAKE_CONST_MOCK0(getValue, std::any(), override);

            MAKE_CONST_MOCK0(getStrValue, std::string(), override);

            MAKE_MOCK1(setValue, void (std::shared_ptr<AttributeStatusRecord>), override);

            MAKE_MOCK1(setValue, void (AttributeResponse&), override);

            MAKE_MOCK3(setValue, void (uint8_t, uint8_t, uint8_t*), override);

            MAKE_MOCK1(setStatus, void (uint8_t ), override);

            MAKE_MOCK1(requestValue, void ( std::unique_ptr<ResponseCallback<ZCLAttribute *>> &&), override);

            MAKE_CONST_MOCK0(isAvailable, bool(), override);

            MAKE_CONST_MOCK0(isUnsupported, bool(), override);

            MAKE_MOCK0(getStatus, Status(), override);

            MAKE_CONST_MOCK0(getIdentifier, int(), override);

            MAKE_CONST_MOCK0(isReadOnly, bool(), override);

            MAKE_MOCK0(getClusterParent, Cluster *(), override);
        };

    }
/* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZCLBITMAP8BITATTRIBUTEMOCK_H_ */
