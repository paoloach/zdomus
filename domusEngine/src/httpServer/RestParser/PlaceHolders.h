/*
 * PlaceHolders.h
 *
 *  Created on: 20/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_HTTPSERVER_RESTPARSER_PLACEHOLDERS_H_
#define SRC_HTTPSERVER_RESTPARSER_PLACEHOLDERS_H_

#include <boost/lexical_cast.hpp>

#include "RestPath.h"
#include "PathReceived.h"
#include "Exceptions/QueryParamNotFound.h"

namespace zigbee {
namespace http {

class PlaceHolders {
public:
	PlaceHolders(RestPath && restPath, PathReceived && pathReceived) noexcept;
	PlaceHolders(const RestPath & restPath, PathReceived && pathReceived) noexcept;

	template <typename T, typename P> T get(P && placeholderName) const;
	template <typename T, typename P> T getQueryParam(P && paramName) const;
private:
	std::string getInternal(std::string &&) const ;
	RestPath restPath;
	PathReceived pathReceived;
};


template<typename T, typename F>
inline T http::PlaceHolders::get(F && placeolder) const {
	return boost::lexical_cast<T>(getInternal(std::forward<F>(placeolder)));
}

template<typename T, typename P>
inline T http::PlaceHolders::getQueryParam(P && param) const {
	auto queryParams = pathReceived.getQueryParams();
	auto found = queryParams.find(std::forward<P>(param));
	if (found == queryParams.end()){
		throw QueryParamNotFound{};
	}
	return boost::lexical_cast<T>(found->second);
}

} /* namespace http */
} /* namespace zigbee */

#endif /* SRC_HTTPSERVER_RESTPARSER_PLACEHOLDERS_H_ */
