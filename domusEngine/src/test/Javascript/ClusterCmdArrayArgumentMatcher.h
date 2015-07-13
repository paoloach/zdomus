/*
 * ClusterCmdArgumentMatcher.h
 *
 *  Created on: 06/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_CLUSTERCMDARRAYARGUMENTMATCHER_H_
#define SRC_TEST_JAVASCRIPT_CLUSTERCMDARRAYARGUMENTMATCHER_H_

#include <gmock/gmock.h>
#include <zcl/CmdParams/ClusterCmdParams.h>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <initializer_list>

namespace zigbee {
namespace test {

using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

template<typename T1, ZCLTypeDataType z1>
class ClusterCmdArrayArgumentMatcher: public MatcherInterface<std::vector<uint8_t> > {
public:
	ClusterCmdArrayArgumentMatcher(std::initializer_list<T1> list) :
			 p1(list){

	}
	virtual ~ClusterCmdArrayArgumentMatcher() {}

	virtual bool MatchAndExplain(std::vector<uint8_t>  data, MatchResultListener* ) const override {
		std::vector<uint8_t> expected;
		std::vector<std::string> expectedString;

		ZCLCmdList<z1> typeP1;
		for(const T1 & t1: p1){
			expectedString.push_back(boost::lexical_cast<std::string>(t1));
		}
		std::vector<uint8_t> p1Data { typeP1.getRaw(expectedString)};
		std::copy(p1Data.begin(), p1Data.end(), std::back_inserter(expected));

		return data == expected;
	}

	virtual void DescribeTo(::std::ostream* os) const override {
		(*os) << "Contain data for argument {" ;
		for(const T1 & t1: p1){
			(*os) << t1 << ", ";
		}
		(*os) << "}";
 	}
private:
	std::vector<T1> p1;
};

template< typename T1, ZCLTypeDataType z1>
inline testing::Matcher<std::vector<uint8_t> > HasArraysArgument(std::initializer_list<T1> list) {
  return testing::MakeMatcher(new ClusterCmdArrayArgumentMatcher<T1, z1>(list));
}

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_CLUSTERCMDARRAYARGUMENTMATCHER_H_ */
