/*
 * PathReceived.cpp

 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */
#include<boost/tokenizer.hpp>
#include "PathReceived.h"

using std::string;

namespace zigbee {
namespace http {

PathReceived::PathReceived(string && uri) noexcept {
	using Separator=boost::char_separator<char>;
	using Tokenizer=boost::tokenizer<Separator>;
	auto queryDelim = uri.find('?');

	if (queryDelim == std::string::npos) {
		createElements(std::move(uri));
	} else {
		createElements(uri.substr(0, queryDelim));
		auto queryString = uri.substr(queryDelim+1);
		Separator separator("&");
		Tokenizer tokens(queryString, separator);
		for (string token: tokens){
			RestQuery restQuery(std::move(token));
			queryParams.insert({restQuery.name, restQuery});
		}

	}

}
void PathReceived::createElements(std::string&& uri) {
	boost::filesystem::path path(uri);
	for (const auto& element : path) {
		if (element != "/" && element != R"(\)")
			elements.push_back(element.string());
	}

}
} // end namespace http
} /* namespace zigbee */

