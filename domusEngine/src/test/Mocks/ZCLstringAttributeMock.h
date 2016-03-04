/*
 * ZCLstringAttributeMock.h
 *
 *  Created on: 11/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZCLSTRINGATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_ZCLSTRINGATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <zcl/attributeTypes/ZCLstringAttribute.h>

namespace zigbee {
namespace test {

class ZCL_string_AttributeMock : public ZCL_string_Attribute{
public:
	ZCL_string_AttributeMock();
	virtual ~ZCL_string_AttributeMock();

	MOCK_METHOD1(sendValue, void (const std::string &  newValue));
	MOCK_CONST_METHOD0(getValue, boost::any () );
	MOCK_METHOD1(internalSetValue, void (std::shared_ptr<AttributeStatusRecord> rawData));
	MOCK_METHOD0(getZCLType, ZCLTypeDataType () );
	MOCK_METHOD1(setValue, void (std::shared_ptr<AttributeStatusRecord> rawData));
	MOCK_METHOD0(requestValue, void ());
	MOCK_CONST_METHOD0(isAvailable, bool () );
	MOCK_CONST_METHOD0(isUnsupported, bool () );
	MOCK_METHOD0(getStatus, Status () );
	MOCK_CONST_METHOD0(getIdentifier, int ());
	MOCK_CONST_METHOD0(getName, std::experimental::string_view ());
	MOCK_CONST_METHOD0(isReadOnly, bool () );
	MOCK_METHOD1(onChange, ListenerOnChange(std::function<void()> changeSignal));
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZCLSTRINGATTRIBUTEMOCK_H_ */
