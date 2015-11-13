/*
 * HTTPServerRequestMock.h
 *
 *  Created on: 13/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_HTTP_HTTPSERVERREQUESTMOCK_H_
#define SRC_TEST_MOCKS_HTTP_HTTPSERVERREQUESTMOCK_H_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/SocketAddress.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


namespace zigbee {
namespace http {
namespace test {

class HTTPServerRequestMock : public Poco::Net::HTTPServerRequest {
public:
	HTTPServerRequestMock(const std::string method, const std::string uri);
	HTTPServerRequestMock();
	virtual ~HTTPServerRequestMock();
	MOCK_METHOD0(stream, std::istream& ());
	MOCK_CONST_METHOD0(expectContinue, bool ());
	MOCK_CONST_METHOD0(clientAddress, const Poco::Net::SocketAddress& () );
	MOCK_CONST_METHOD0(serverAddress, const Poco::Net::SocketAddress& () );
	MOCK_CONST_METHOD0(serverParams, const Poco::Net::HTTPServerParams& () );
	MOCK_CONST_METHOD0(response, Poco::Net::HTTPServerResponse& () );
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_HTTP_HTTPSERVERREQUESTMOCK_H_ */
