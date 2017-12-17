/*
 * main.cpp
 *
 *  Created on: 26/nov/2014
 *      Author: Paolo Achdjian
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}


