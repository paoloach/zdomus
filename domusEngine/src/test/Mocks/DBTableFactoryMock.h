/*
 * DBTableFactoryMock.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_DBTABLEFACTORYMOCK_H_
#define SRC_TEST_MOCKS_DBTABLEFACTORYMOCK_H_

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../Database/DBTableFactory.h"

namespace zigbee {
namespace test {

class DBTableFactoryMock : public DBTableFactory{
public:
	DBTableFactoryMock();
	virtual ~DBTableFactoryMock();

	MOCK_CONST_METHOD1(getTable,  DBTable * (const std::string & tableName) );
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_DBTABLEFACTORYMOCK_H_ */
