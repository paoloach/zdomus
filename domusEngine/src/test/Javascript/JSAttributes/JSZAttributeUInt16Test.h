/*
 * JSZAttributeUInt16.h
 *
 *  Created on: 09/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEUINT16TEST_H_
#define SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEUINT16TEST_H_


#include <gmock/gmock.h>
#include <tuple>
#include "JSAttributeTest.h"
#include "../../Mocks/ZCLUint16AttributeMock.h"

namespace zigbee {
namespace test {

class JSZAttributeUInt16Test : public JSAttributeTest{
public:
	class ActionOnCall: public ::testing::ActionInterface<boost::signals2::connection(boost::signals2::slot<void(), boost::function<void()> >)> {
	public:
		boost::signals2::connection Perform(const ArgumentTuple& args) {
			boost::signals2::connection result;

			boost::signals2::slot<void(), boost::function<void()> > slot = std::get<0>(args);
			result = changeSignal.connect(slot);
			return result;
		}

		OnChangeSignal changeSignal;
		// boost::signals2::slot<void(), boost::function<void()> > func;
	};

protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
protected:
	std::shared_ptr<JSZAttribute> jsZAttribute;
	std::shared_ptr<ZCLUint16AttributeMock> zclUint16Attribute;
	ActionOnCall action;

};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_JSATTRIBUTES_JSZATTRIBUTEUINT16TEST_H_ */