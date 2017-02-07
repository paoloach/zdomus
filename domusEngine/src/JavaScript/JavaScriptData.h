/*
 * JavaScriptData.h
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPTDATA_H_
#define SRC_JAVASCRIPTDATA_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time.hpp>
#include <chrono>

namespace zigbee {

    class JavaScriptData {
    public:
        JavaScriptData(boost::property_tree::ptree &properties);

    public:
        std::string getCode() const { return code; }

        std::chrono::seconds  getPeriod() const { return period; }

        std::string getName() const { return name; }

        bool hasError() const {return error;}
    private:
        std::string name;
        std::string code;
        std::chrono::seconds  period;
        bool error;
    };

} /* namespace zigbee */

#endif /* SRC_JAVASCRIPTDATA_H_ */
