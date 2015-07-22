/*
 * ZCLUint8AttributeMock.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZCLUINT8ATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_ZCLUINT8ATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <zcl/attributeTypes/ZCLuint8Attribute.h>

namespace zigbee {
namespace test {

class ZCLUint8AttributeMock: public ZCL_uint8_Attribute {
public:
	ZCLUint8AttributeMock();
	virtual ~ZCLUint8AttributeMock();

	MOCK_CONST_METHOD0(getValue, boost::any () );
	MOCK_METHOD1(sendValue, void (uint8_t newValue));
	MOCK_METHOD1(internalSetValue, void (std::shared_ptr<AttributeStatusRecord> rawData));
	MOCK_METHOD0(getZCLType, ZCLTypeDataType () );
	MOCK_METHOD1(setValue, void (std::shared_ptr<AttributeStatusRecord> rawData));
	MOCK_METHOD0(requestValue, void ());
	MOCK_CONST_METHOD0(isAvailable, bool () );
	MOCK_CONST_METHOD0(isUnsupported, bool () );
	MOCK_METHOD0(getStatus, Status () );
	MOCK_CONST_METHOD0(getIdentifier, int ());
	MOCK_CONST_METHOD0(getName, std::string ());
	MOCK_CONST_METHOD0(isReadOnly, bool () );
	MOCK_METHOD1(onChange, boost::signals2::connection (OnChangeSignal::slot_type changeSignal));
};

}
/* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZCLUINT8ATTRIBUTEMOCK_H_ */