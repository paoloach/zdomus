/*
 * HTTPServerResponseMock.h
 *
 *  Created on: 14/apr/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_TEST_MOCKS_HTTP_HTTPSERVERRESPONSEMOCK_H_
#define SRC_TEST_MOCKS_HTTP_HTTPSERVERRESPONSEMOCK_H_

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/SocketAddress.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace zigbee {
namespace http {
namespace test {

class HTTPServerResponseMock: public Poco::Net::HTTPServerResponse {
public:
	HTTPServerResponseMock();
	virtual ~HTTPServerResponseMock();
public:
	MOCK_METHOD0(sendContinue, void ());
	MOCK_METHOD0(send, std::ostream& ());
	MOCK_METHOD2(sendFile, void (const std::string& path, const std::string& mediaType));
	MOCK_METHOD2(sendBuffer, void (const void* pBuffer, std::size_t length));
	MOCK_METHOD2(redirect, void (const std::string& uri, HTTPStatus status ));
	MOCK_METHOD1(requireAuthentication, void (const std::string& realm) );
	MOCK_CONST_METHOD0(sent, bool () );
};

} /* namespace test */
} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_TEST_MOCKS_HTTP_HTTPSERVERRESPONSEMOCK_H_ */
