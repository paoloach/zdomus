/*
 * ZCLAttributeMock.h
 *
 *  Created on: 05/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_ZCLATTRIBUTEMOCK_H_
#define SRC_TEST_MOCKS_ZCLATTRIBUTEMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <zcl/ZCLAttribute.h>

namespace zigbee {
namespace test {

class ZCLAttributeMock: public ZCLAttribute {
public:
	ZCLAttributeMock(const std::shared_ptr<ZigbeeDevice> & zigbeeDevice, Cluster * parent,int identifier, ZCLTypeDataType zclType, const std::string & name, bool readOnly);
	virtual ~ZCLAttributeMock();

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
	MOCK_METHOD1(onChange, ListenerOnChange(std::function<void()>  changeSignal));
	MOCK_CONST_METHOD0(getValue, boost::any () );
};

}
/* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_ZCLATTRIBUTEMOCK_H_ */
