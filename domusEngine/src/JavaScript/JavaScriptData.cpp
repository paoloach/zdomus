/*
 * JavaScriptData.cpp
 *
 *  Created on: 22/dic/2014
 *      Author: Paolo Achdjian
 */

#include <iostream>

#include "JavaScriptData.h"
#include "jsonFields.h"

namespace zigbee {

using boost::property_tree::ptree;
using boost::property_tree::ptree_error;

JavaScriptData::JavaScriptData(ptree & properties) {
	try {
		if (properties.count(FILENAME_NAME) > 0) {
			std::string filename = properties.get<std::string>(FILENAME_NAME);
			std::ifstream fileStream(filename);
			if (fileStream.fail()){
				std::cerr << "unable to read file " << filename << std::endl;
			}
			fileStream.seekg(0, std::ios::end);
			size_t size = fileStream.tellg();
			code.resize(size);
			fileStream.seekg(0);
			fileStream.read(&code[0], size);
		} else {
			code = properties.get<std::string>(CODE_NAME);
		}
		period = properties.get<boost::posix_time::time_duration>(PERIOD_NAME);
		auto nameOptional = properties.get_optional<std::string>(NAME);
		if (nameOptional){
			name = nameOptional.get();
		} else {
			name = "noname";
		}
	} catch (const ptree_error & e) {
		std::cerr << "missing tag " << e.what() << std::endl;
	}

}

} /* namespace zigbee */
