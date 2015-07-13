/*
 * ClusterCmdArgumentMatcher.h
 *
 *  Created on: 06/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_JAVASCRIPT_CLUSTERCMDARGUMENTMATCHER_H_
#define SRC_TEST_JAVASCRIPT_CLUSTERCMDARGUMENTMATCHER_H_

#include <gmock/gmock.h>
#include <zcl/CmdParams/ClusterCmdParams.h>
#include <vector>

namespace zigbee {
namespace test {

using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

template<typename T1, typename T2, ZCLTypeDataType z1, ZCLTypeDataType z2>
class ClusterCmdArgumentMatcher: public MatcherInterface<std::vector<uint8_t> > {
public:
	ClusterCmdArgumentMatcher(const T1 & t1, const T2 & t2) :
			p1(t1), p2(t2) {

	}
	virtual ~ClusterCmdArgumentMatcher() {}

	virtual bool MatchAndExplain(std::vector<uint8_t>  data, MatchResultListener* ) const override {
		std::vector<uint8_t> expected;

		ZCLType<z1> typeP1;
		ZCLType<z2> typeP2;
		std::vector<uint8_t> p1Data { typeP1.getRaw(p1) };
		std::vector<uint8_t> p2Data { typeP2.getRaw(p2) };
		std::copy(p1Data.begin(), p1Data.end(), std::back_inserter(expected));
		std::copy(p2Data.begin(), p2Data.end(), std::back_inserter(expected));

		return data == expected;
	}

	virtual void DescribeTo(::std::ostream* os) const override {
		(*os) << "containt data for argument " << p1 << ", and " << p2;
	}
private:
	T1 p1;
	T2 p2;
};

template<typename T1, typename T2, ZCLTypeDataType z1, ZCLTypeDataType z2>
inline testing::Matcher<std::vector<uint8_t> > HasArgument(T1 t1, T2 t2) {
  return testing::MakeMatcher(new ClusterCmdArgumentMatcher<T1,T2,z1,z2>(t1,t2));
}

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_JAVASCRIPT_CLUSTERCMDARGUMENTMATCHER_H_ */
