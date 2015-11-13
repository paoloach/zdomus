/*
 * PathTest.cpp
 *
 *  Created on: 08/apr/2015
 *      Author: Paolo Achdjian
 */

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include "PathTest.h"


namespace zigbee {
namespace test {
namespace http {

using std::string;
using namespace testing;

PathTest::~PathTest() {
}

void PathTest::SetUp() {
}

void PathTest::TearDown() {
}

TEST_F( PathTest, testPathParent) {
	string strPath1="path1";
	string strPath2="path2";
	string strPath3="path3";
	boost::filesystem::path path(strPath1+"/"+ strPath2);
	boost::filesystem::path path2(strPath1+"/"+ strPath2+"/"+strPath3);

//	string parentPath = boost::lexical_cast<std::string>(path2.parent_path());
//	ASSERT_THAT(parentPath, strPath1+"/"+ strPath2);
	ASSERT_THAT(path2.parent_path().compare(path) , 0) << "expected " << path << " but got " << path2.parent_path();

}

TEST_F( PathTest, testPathIterator) {
	string strPath1="path1";
	string strPath2="path2";
	boost::filesystem::path path(strPath1+"/"+ strPath2);

	auto pathIter = path.begin();

	ASSERT_THAT(pathIter->compare(strPath1),0);
	pathIter++;
	ASSERT_THAT(pathIter->compare(strPath2),0);
}

TEST_F( PathTest, testPathIteratorQuery) {
	string strPath1="path1";
	string strPath2="path2?a=43&b=4"  ;
	boost::filesystem::path path(strPath1+"/"+ strPath2);

	auto pathIter = path.begin();

	ASSERT_THAT(pathIter->compare(strPath1),0);
	pathIter++;
	std::cout << *pathIter << std::endl;
	ASSERT_THAT(pathIter->compare(strPath2),0);
}

} /* namespace http */
} /* namespace test */
} /* namespace zigbee */
