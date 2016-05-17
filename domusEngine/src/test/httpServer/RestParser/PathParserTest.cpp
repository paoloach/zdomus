/*
 * PathParserTest.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../../httpServer/RestParser/PathReceived.h"

using namespace testing;
namespace zigbee {
    namespace http {
        namespace test {
            TEST(PathParserTest, parsePath) {
                PathReceived pathParser("/p1/p2/p3");

                ASSERT_THAT(pathParser.getSize(), Eq(3u));
                auto element = pathParser.begin();
                ASSERT_THAT(*element++, Eq("p1"));
                ASSERT_THAT(*element++, Eq("p2"));
                ASSERT_THAT(*element++, Eq("p3"));
            }

            TEST(PathParserTest, parsePathWithQueryParams) {
                PathReceived pathParser("/p1/p2/p3?p4=5&p6=7");

                ASSERT_THAT(pathParser.getSize(), Eq(3u));
                auto element = pathParser.begin();
                ASSERT_THAT(*element++, Eq("p1"));
                ASSERT_THAT(*element++, Eq("p2"));
                ASSERT_THAT(*element++, Eq("p3"));

                auto queryParams = pathParser.getQueryParams();
                ASSERT_THAT(queryParams.size(), 2);
                ASSERT_THAT(queryParams["p4"].values[0], Eq("5"));
                ASSERT_THAT(queryParams["p6"].values[0], Eq("7"));
            }

            TEST(PathParserTest, parsePathWithQueryParamsInvalid) {
                PathReceived pathParser("/p1/p2/p3?p4=5&p6&p8=9");

                ASSERT_THAT(pathParser.getSize(), Eq(3u));
                auto element = pathParser.begin();
                ASSERT_THAT(*element++, Eq("p1"));
                ASSERT_THAT(*element++, Eq("p2"));
                ASSERT_THAT(*element++, Eq("p3"));

                auto queryParams = pathParser.getQueryParams();
                ASSERT_THAT(queryParams.size(), 3);
                ASSERT_THAT(queryParams["p4"].values[0], Eq("5"));
                ASSERT_THAT(queryParams["p6"].values.size(), Eq(0));
                ASSERT_THAT(queryParams["p8"].values[0], Eq("9"));
            }

            TEST(PathParserTest, parsePathWithQueryParamsList) {
                PathReceived pathParser("/p1/p2/p3?id=3,5");

                ASSERT_THAT(pathParser.getSize(), Eq(3u));
                auto element = pathParser.begin();
                ASSERT_THAT(*element++, Eq("p1"));
                ASSERT_THAT(*element++, Eq("p2"));
                ASSERT_THAT(*element++, Eq("p3"));

                auto queryParams = pathParser.getQueryParams();
                ASSERT_THAT(queryParams.size(), 1);
                ASSERT_THAT(queryParams["id"].values.size(), Eq(2));
                ASSERT_THAT(queryParams["id"].values[0], Eq("3"));
                ASSERT_THAT(queryParams["id"].values[1], Eq("5"));
            }


        }
    }
} /* namespace zigbee */
