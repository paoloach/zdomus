/*
 * PathElementTest.cpp
 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */

#include "../../../httpServer/RestParser/PathElement.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
namespace zigbee {
    namespace http {
        namespace test {
            TEST(PathElementTest, pathString) {
                std::string path = "path";

                PathElement pathElement(path);

                ASSERT_THAT(pathElement.isPlaceholder(), Eq(false));
                ASSERT_THAT(pathElement.getValue(), Eq(path));
            }

            TEST(PathElementTest, isPlaceholder) {
                std::string placeHolder = "{path}";

                PathElement pathElement(placeHolder);

                ASSERT_THAT(pathElement.isPlaceholder(), Eq(true));
                ASSERT_THAT(pathElement.getValue(), Eq("path"));
            }

        }
    } /* namespace http */
} /* namespace zigbee */
