/*
 * ZCLAttributeMock.h
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZCLATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_ZCLATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

#include <zcl/ZCLAttribute.h>
#include <zigbee/messageStructure/ReadAttributeResponseMessage.h>

namespace zigbee {
    namespace test {

        class ZCLAttributeMock : public ZCLAttribute {
        public:
            ZCLAttributeMock();

            virtual ~ZCLAttributeMock();

            MAKE_MOCK0(getAttributeRawValue, ZclAttributeRawValue & (),override);

            MAKE_CONST_MOCK0(getValue, std::any(),override);

            MAKE_MOCK1(setValue, void (std::any &),override);

            MAKE_MOCK1(setRawValue, void(uint8_t*rawData),override);

            MAKE_CONST_MOCK0(getStrValue, std::string(),override);

            MAKE_MOCK0(getZCLType, ZCLTypeDataType(),override);

            MAKE_MOCK1(setValue, void (AttributeResponse &attributeResponse), override);

            MAKE_MOCK3(setValue, void (uint8_t status, uint8_t dataType, uint8_t *rawData), override);

            MAKE_MOCK1(setStatus, void (uint8_t status),override);
            MAKE_MOCK0(getStatus, Status(),override);
            MAKE_MOCK1(requestValue, void(std::unique_ptr<ResponseCallback<ZCLAttribute *>> &&),override);

            MAKE_CONST_MOCK0(isAvailable, bool(),override);

            MAKE_CONST_MOCK0(isUnsupported, bool(),override);

            MAKE_CONST_MOCK0(getIdentifier, int(),override);

            MAKE_CONST_MOCK0(getName, std::string_view(),override);

            MAKE_CONST_MOCK0(isReadOnly, bool(),override);

            MAKE_MOCK0(getClusterParent, Cluster *(), override);



        };

    }
/* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZCLATTRIBUTEMOCK_H_ */
