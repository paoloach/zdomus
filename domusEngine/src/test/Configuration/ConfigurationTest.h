/*
 * ConfigurationTest.h
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_CONFIGURATIONTEST_H_
#define SRC_TEST_CONFIGURATIONTEST_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "../../Configuration/Configuration.h"

namespace zigbee {
namespace test {

class ConfigurationTest : public ::testing::Test{
public:
	virtual ~ConfigurationTest();
protected:
	virtual void SetUp() ;
	virtual void TearDown() ;
protected:
	std::string getConfigWith1JS();
	std::string getConfigWithTwoJS();
	std::shared_ptr<Configuration> conf;
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_CONFIGURATIONTEST_H_ */
