//
// Created by paolo on 16/05/16.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../../httpServer/RestParser/RestQuery.h"

namespace zigbee {
    namespace http {
        namespace test {
            using namespace testing;

            TEST(RestQuery, CreationZeroElement){
                RestQuery restQuery("id");
                ASSERT_THAT(restQuery.name,Eq("id"));
                ASSERT_THAT(restQuery.values.size(), Eq(0));
            }

            TEST(RestQuery, CreationOneElement){
                RestQuery restQuery("id=1");
                ASSERT_THAT(restQuery.name,Eq("id"));
                ASSERT_THAT(restQuery.values.size(), Eq(1));
                ASSERT_THAT(restQuery.values[0], Eq("1"));
            }

            TEST(RestQuery, CreationTwoElement){
                RestQuery restQuery("id=1,2");
                ASSERT_THAT(restQuery.name,Eq("id"));
                ASSERT_THAT(restQuery.values.size(), Eq(2));
                ASSERT_THAT(restQuery.values[0], Eq("1"));
                ASSERT_THAT(restQuery.values[1], Eq("2"));
            }


            TEST(RestQuery, CreationTwoElement_period){
                RestQuery restQuery("id=1,2,");
                ASSERT_THAT(restQuery.name,Eq("id"));
                ASSERT_THAT(restQuery.values.size(), Eq(2));
                ASSERT_THAT(restQuery.values[0], Eq("1"));
                ASSERT_THAT(restQuery.values[1], Eq("2"));
            }
        }
    }
}