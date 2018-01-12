/*
 * DBTableMock.h
 *
 *  Created on: 20/gen/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_DBTABLEMOCK_H_
#define SRC_TEST_MOCKS_DBTABLEMOCK_H_

#include <gtest/gtest.h>
#include "../../trompeloeil/src/trompeloeil/include/trompeloeil.hpp"

#include "../../Database/DBTable.h"

namespace zigbee {
namespace test {

class DBTableMock : public DBTable{
public:
	DBTableMock();
	virtual ~DBTableMock();

	MAKE_MOCK1(find, ResultSet  (const std::string & query));
    MAKE_MOCK1(insert,  void (DBRow * dbRow) );
};

} /* namespace test */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_DBTABLEMOCK_H_ */
