/*
 * PathReceived.cpp

 *
 *  Created on: 19/mag/2015
 *      Author: Paolo Achdjian
 */
#include<boost/tokenizer.hpp>
#include "PathReceived.h"

namespace zigbee {
namespace http {

PathReceived::PathReceived(std::string && uri) noexcept {
	using Separator=boost::char_separator<char>;
	using Tokenizer=boost::tokenizer<Separator>;
	auto queryDelim = uri.find('?');

	if (queryDelim == std::string::npos) {
		createElements(std::move(uri));
	} else {
		createElements(std::move(uri.substr(0, queryDelim)));
		auto queryString = uri.substr(queryDelim+1);
		Separator separator("&");
		Tokenizer tokens(queryString, separator);
		for (const auto & token: tokens){
			auto queryDelim = token.find('=');
			if (queryDelim == std::string::npos){
				queryParams[token];
			} else {
				auto key = token.substr(0,queryDelim);
				queryParams[key] = token.substr(queryDelim+1);
			}
		}

	}

}
void PathReceived::createElements(std::string&& uri) {
	boost::filesystem::path path(uri);
	for (auto element : path) {
		if (element != "/" && element != "\\")
			elements.push_back(element.string());
	}

}
} // end namespace http
} /* namespace zigbee */

