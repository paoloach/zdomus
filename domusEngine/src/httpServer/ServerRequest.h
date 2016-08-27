//
// Created by paolo on 15/07/16.
//

#ifndef DOMUS_ENGINE_SERVERREQUEST_H
#define DOMUS_ENGINE_SERVERREQUEST_H

#include <Poco/Net/HTTPServerRequest.h>
#include <experimental/string_view>

namespace zigbee {
    namespace http {
        class ServerRequest {
        public :
            static std::experimental::string_view JSON_TYPE;
        public:
            ServerRequest(Poco::Net::HTTPServerRequest & request):request(request){
            }

            virtual std::istream& stream(){
                return request.stream();
            }

            virtual const std::string & getContentType() {
                return request.getContentType();
            }

            virtual const std::string & getURI() {
                return request.getURI();
            }

            bool isApplicationJSon();
        private:
            Poco::Net::HTTPServerRequest & request;
        };
    }
}


#endif //DOMUS_ENGINE_SERVERREQUEST_H
