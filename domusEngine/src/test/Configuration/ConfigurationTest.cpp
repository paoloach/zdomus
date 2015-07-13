/*
 * ConfigurationTest.cpp
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/chrono.hpp>

#include "ConfigurationTest.h"
#include "../../Configuration/Configuration.h"
#include "jsonFields.h"

namespace zigbee {
namespace test {

using namespace boost::property_tree::xml_parser;
using boost::property_tree::ptree;
using std::string;
using std::stringstream;
using namespace testing;
using namespace boost::posix_time;

static const std::string CODE1 = "this is a javascript code";
static const std::string CODE2 = "this is another javascript code";
static const time_duration PERIOD1 = seconds(20);
static const time_duration PERIOD2 = seconds(40);

ConfigurationTest::~ConfigurationTest() {
}

void ConfigurationTest::SetUp() {


}

void ConfigurationTest::TearDown() {
}

string ConfigurationTest::getConfigWith1JS() {
	std::stringstream xmlStream {};
	ptree trunck {};
	ptree js1 {};

	js1.put(CODE_NAME, CODE1);
	js1.put(PERIOD_NAME, PERIOD1);
	trunck.push_back( {JAVASCRIPT_NAME,js1} );
	write_xml(xmlStream, trunck);
	return xmlStream.str();
}

string ConfigurationTest::getConfigWithTwoJS() {
	std::stringstream xmlStream {};
	ptree trunck {};
	ptree js1 {};
	ptree js2 {};

	js1.put(CODE_NAME, CODE1);
	js1.put(PERIOD_NAME, PERIOD1);
	js2.put(CODE_NAME, CODE2);
	js2.put(PERIOD_NAME, PERIOD2);
	trunck.push_back( {JAVASCRIPT_NAME,js1} );
	trunck.push_back( {JAVASCRIPT_NAME,js2} );
	write_xml(xmlStream, trunck);
	return xmlStream.str();
}

TEST_F( ConfigurationTest, configuraitonWithOneJS) {
	string xml = getConfigWith1JS();

	std::stringstream xmlStream {xml};

	conf = std::make_shared<Configuration>(xmlStream);
	auto jss = conf->getJavascriptData();
	ASSERT_THAT(jss.size(), Eq(1));
	auto element0 = (*jss.begin()).second;
	ASSERT_THAT(element0->getCode(), Eq(CODE1));
	ASSERT_THAT(element0->getPeriod(), Eq(PERIOD1));
}

TEST_F( ConfigurationTest, configuraitonWithTwoJS) {
	string xml = getConfigWithTwoJS();

	std::stringstream xmlStream {xml};

	conf = std::make_shared<Configuration>(xmlStream);
	auto jss = conf->getJavascriptData();
	ASSERT_THAT(jss.size(), Eq(2));
	auto jss_iter = jss.begin();
	auto element0 = (*jss_iter).second;
	jss_iter++;
	auto element1 = (*jss_iter).second;

	ASSERT_THAT(element0->getCode(), Eq(CODE1));
	ASSERT_THAT(element0->getPeriod(), Eq(PERIOD1));
	ASSERT_THAT(element1->getCode(), Eq(CODE2));
	ASSERT_THAT(element1->getPeriod(), Eq(PERIOD2));

}

} /* namespace test */
} /* namespace zigbee */
