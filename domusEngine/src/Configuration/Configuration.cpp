/*
 * Configuration.cpp
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

#include "Configuration.h"
#include "jsonFields.h"

namespace zigbee {

    using namespace boost::property_tree::xml_parser;
    using boost::property_tree::ptree;
    using boost::property_tree::ptree_error;

    Configuration::Configuration(std::istream &config) {
        try {
            read_xml(config, configuration);
            auto javascripts = configuration.equal_range(JAVASCRIPT_NAME);
            for (; javascripts.first != javascripts.second; javascripts.first++) {
                auto js = std::make_shared<JavaScriptData>(javascripts.first->second);
                if (js->hasError()){
                    BOOST_LOG_TRIVIAL(error) << "The configuration " << js->getName() << " has error and is skipped";
                } else {
                    BOOST_LOG_TRIVIAL(trace) << "Added configuraion " << js->getName();
                    jsDatas.insert({js->getName(), js});
                }
            }
        } catch (const ptree_error &e) {
            BOOST_LOG_TRIVIAL(error) << "Error reading the config file: " << e.what();
            exit(-1);
        }

    }


} /* namespace zigbee */
