/*
 * RestActionsTest.cpp
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#include "../../../httpServer/RestParser/PathReceived.h"
#include "../../../httpServer/RestParser/RestPath.h"
#include "../../../httpServer/RestParser/RestActions.h"

#include "RestActionsTest.h"
#include "../../Mocks/http/HTTPServerResponseMock.h"
#include "../../Mocks/http/HTTPServerRequestMock.h"
#include <Poco/Net/HTTPServerParams.h>

namespace zigbee {
namespace http {
namespace test {

using namespace testing;

RestActionsTest::RestActionsTest() {
}

RestActionsTest::~RestActionsTest() {
}

TEST_F( RestActionsTest, matchRestPath) {
	bool pathP1=false;
	bool pathP2=false;
	RestPath restPath1 {"/p1/{p2}/p3/{p4}"};
	RestPath restPath2 {"/p1/{p2}/p5/{p6}"};
	HTTPServerResponseMock response;
	HTTPServerRequestMock request{"GET","aa"};

	RestActions restActions;
	restActions.addActions(std::move(restPath1), [&](const PlaceHolders &, Poco::Net::HTTPServerRequest& , Poco::Net::HTTPServerResponse& ){pathP1=true;});
	restActions.addActions(std::move(restPath2), [&](const PlaceHolders &, Poco::Net::HTTPServerRequest&,Poco::Net::HTTPServerResponse& ){pathP2=true;});

	restActions.execute(PathReceived("/p1/p2val/p3/p4val"),request, response);

	ASSERT_THAT(pathP1, Eq(true));
}

TEST_F( RestActionsTest, rightPlaceOlder) {
	std::string pathP1;
	std::string pathP2;
	RestPath restPath1 {"/p1/{p2}/p3/{p4}"};
	RestPath restPath2 {"/p1/{p2}/p5/{p6}"};
	HTTPServerResponseMock response;
	HTTPServerRequestMock request{"GET","aa"};;

	RestActions restActions;
	restActions.addActions(std::move(restPath1), [&](const PlaceHolders &ph, Poco::Net::HTTPServerRequest&,Poco::Net::HTTPServerResponse& ) {pathP1=ph.get<std::string>("p2");});
	restActions.addActions(std::move(restPath2), [&](const PlaceHolders &ph, Poco::Net::HTTPServerRequest&,Poco::Net::HTTPServerResponse& ) {pathP2=ph.get<std::string>("p2");});

	restActions.execute(PathReceived("/p1/p2val/p3/p4val"),request, response);

	ASSERT_THAT(pathP1, Eq("p2val"));
}

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */
