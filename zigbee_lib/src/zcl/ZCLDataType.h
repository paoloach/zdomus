/*
 * ZCLTypeDataType.h
 *
 *  Created on: 23/lug/2014
 *      Author: Paolo Achdjian
 */

#ifndef ZCLTypeDATATYPE_H_
#define ZCLTypeDATATYPE_H_

#include <string.h>
#include <ostream>
#include <vector>
#include <map>
#include <boost/lexical_cast.hpp>

enum class ZCLTypeDataType {
	ZCLTypeInvalid = -1,
	ZCLType8bit = 0x8,
	ZCLType16bit = 0x9,
	ZCLType24bit = 0xA,
	ZCLType32bit = 0xB,
	ZCLType40bit = 0xC,
	ZCLType48bit = 0xD,
	ZCLType56bit = 0xE,
	ZCLType64bit = 0xF,
	ZCLTypeBool = 0x10,
	ZCLType8bitBitmap = 0x18,
	ZCLType16bitBitmap = 0x19,
	ZCLType24bitBitmap = 0x1A,
	ZCLType32bitBitmap = 0x1B,
	ZCLType40bitBitmap = 0x1C,
	ZCLType48bitBitmap = 0x1D,
	ZCLType56bitBitmap = 0x1E,
	ZCLType64bitBitmap = 0x1F,
	ZCLTypeUInt8 = 0x20,
	ZCLTypeUInt16 = 0x21,
	ZCLTypeUInt24 = 0x22,
	ZCLTypeUInt32 = 0x23,
	ZCLTypeUInt40 = 0x24,
	ZCLTypeUInt48 = 0x25,
	ZCLTypeUInt56 = 0x26,
	ZCLTypeUInt64 = 0x27,
	ZCLTypeSInt8 = 0x28,
	ZCLTypeSInt16 = 0x29,
	ZCLTypeSInt24 = 0x2A,
	ZCLTypeSInt32 = 0x2B,
	ZCLTypeSInt40 = 0x2C,
	ZCLTypeSInt48 = 0x2D,
	ZCLTypeSInt56 = 0x2E,
	ZCLTypeSInt64 = 0x2F,
	ZCLTypeenum8 = 0x30,
	ZCLTypeenum16 = 0x31,
	ZCLTypeFloatSemiPrecision = 0x38,
	ZCLTypeFloatSinglePrecision = 0x39,
	ZCLTypeFloatDoublePrecision = 0x3A,
	ZCLTypeStringOctect = 0x41,
	ZCLTypeStringChar = 0x42,
	ZCLTypeStringLongOctect = 0x43,
	ZCLTypeStringLongChar = 0x44,
	ZCLTypeArray = 0x48,
	ZCLTypeStructure = 0x4C,
	ZCLTypeTimeOfDay = 0xE0,
	ZCLTypeDate = 0xE1,
	ZCLTypeUTCTime = 0xE2,
	ZCLTypeClusterID = 0xE8,
	ZCLTypeAttributeId = 0xE9,
	ZCLTypeBACnetOID = 0xEA,
	ZCLTypeIEEEaddress = 0xF0,
	ZCLType128BitSecuryKey = 0xF1
};

static const std::map<ZCLTypeDataType, std::string> names {
	{ZCLTypeDataType::ZCLTypeInvalid,"invalid"},
	{ZCLTypeDataType::ZCLType8bit,"8bit"},
	{ZCLTypeDataType::ZCLType16bit ,"16bit"},
	{ZCLTypeDataType::ZCLType24bit ,"24bit"},
	{ZCLTypeDataType::ZCLType32bit ,"32bit"},
	{ZCLTypeDataType::ZCLType40bit ,"40bit"},
	{ZCLTypeDataType::ZCLType48bit ,"48bit"},
	{ZCLTypeDataType::ZCLType56bit ,"56bit"},
	{ZCLTypeDataType::ZCLType64bit ,"64bit"},
	{ZCLTypeDataType::ZCLTypeBool ,"Bool"},
	{ZCLTypeDataType::ZCLType8bitBitmap ,"8bitBitmap"},
	{ZCLTypeDataType::ZCLType16bitBitmap ,"16bitBitmap"},
	{ZCLTypeDataType::ZCLType24bitBitmap ,"24bitBitmap"},
	{ZCLTypeDataType::ZCLType32bitBitmap ,"32bitBitmap"},
	{ZCLTypeDataType::ZCLType40bitBitmap ,"40bitBitmap"},
	{ZCLTypeDataType::ZCLType48bitBitmap ,"48bitBitmap"},
	{ZCLTypeDataType::ZCLType56bitBitmap ,"56bitBitmap"},
	{ZCLTypeDataType::ZCLType64bitBitmap ,"64bitBitmap"},
	{ZCLTypeDataType::ZCLTypeUInt8 ,"UInt8"},
	{ZCLTypeDataType::ZCLTypeUInt16 ,"UInt16"},
	{ZCLTypeDataType::ZCLTypeUInt24 ,"UInt24"},
	{ZCLTypeDataType::ZCLTypeUInt32 ,"UInt32"},
	{ZCLTypeDataType::ZCLTypeUInt40 ,"UInt40"},
	{ZCLTypeDataType::ZCLTypeUInt48 ,"UInt48"},
	{ZCLTypeDataType::ZCLTypeUInt56 ,"UInt56"},
	{ZCLTypeDataType::ZCLTypeUInt64 ,"UInt64"},
	{ZCLTypeDataType::ZCLTypeSInt8 ,"SInt8"},
	{ZCLTypeDataType::ZCLTypeSInt16 ,"SInt16"},
	{ZCLTypeDataType::ZCLTypeSInt24 ,"SInt24"},
	{ZCLTypeDataType::ZCLTypeSInt32 ,"SInt32"},
	{ZCLTypeDataType::ZCLTypeSInt40 ,"SInt40"},
	{ZCLTypeDataType::ZCLTypeSInt48 ,"SInt48"},
	{ZCLTypeDataType::ZCLTypeSInt56 ,"SInt56"},
	{ZCLTypeDataType::ZCLTypeSInt64 ,"SInt64"},
	{ZCLTypeDataType::ZCLTypeenum8 ,"enum8"},
	{ZCLTypeDataType::ZCLTypeenum16 ,"enum16"},
	{ZCLTypeDataType::ZCLTypeFloatSemiPrecision ,"FloatSemiPrecision"},
	{ZCLTypeDataType::ZCLTypeFloatSinglePrecision ,"FloatSinglePrecision"},
	{ZCLTypeDataType::ZCLTypeFloatDoublePrecision ,"FloatDoublePrecision"},
	{ZCLTypeDataType::ZCLTypeStringOctect ,"StringOctect"},
	{ZCLTypeDataType::ZCLTypeStringChar ,"StringChar"},
	{ZCLTypeDataType::ZCLTypeStringLongOctect ,"StringLongOctect"},
	{ZCLTypeDataType::ZCLTypeStringLongChar ,"StringLongChar"},
	{ZCLTypeDataType::ZCLTypeArray ,"Array"},
	{ZCLTypeDataType::ZCLTypeStructure ,"Structure"},
	{ZCLTypeDataType::ZCLTypeTimeOfDay ,"TimeOfDay"},
	{ZCLTypeDataType::ZCLTypeDate ,"Date"},
	{ZCLTypeDataType::ZCLTypeUTCTime ,"UTCTime"},
	{ZCLTypeDataType::ZCLTypeClusterID ,"ClusterID"},
	{ZCLTypeDataType::ZCLTypeAttributeId ,"AttributeId"},
	{ZCLTypeDataType::ZCLTypeBACnetOID ,"BACnetOID"},
	{ZCLTypeDataType::ZCLTypeIEEEaddress ,"IEEEaddress"},
	{ZCLTypeDataType::ZCLType128BitSecuryKey ,"128BitSecuryKey"}
};

class ZCLTypeBase {
public:
	virtual ~ZCLTypeBase() {
	}
	;
	virtual std::vector<uint8_t> getRaw(const std::string & data) const =0;
	virtual std::vector<uint8_t> getRaw(const std::vector<std::string> & data) const=0;
	virtual std::vector<uint8_t> getRaw(uint64_t data) const=0;
	virtual ZCLTypeDataType getZCLDataType() const=0;
};

template<ZCLTypeDataType z>
class ZCLType: public ZCLTypeBase {
public:
	std::vector<uint8_t> getRaw(const std::string &) const override {
		return std::vector<uint8_t> { };
	}
	std::vector<uint8_t> getRaw(const std::vector<std::string> &) const override {
		return std::vector<uint8_t> { };
	}
	std::vector<uint8_t> getRaw(uint64_t) const override {
		return std::vector<uint8_t> { };
	}

	virtual ZCLTypeDataType getZCLDataType() const override {
		return z;
	}
};

template<ZCLTypeDataType arrayType>
class ZCLArrayType: public ZCLTypeBase {
public:
	std::vector<uint8_t> getRaw(const std::string &) const override {
		return std::vector<uint8_t> { };
	}
	std::vector<uint8_t> getRaw(const std::vector<std::string> & raw) const override {
		std::vector<uint8_t> result;

		result.push_back(static_cast<unsigned char>(arrayType));
		result.push_back(raw.size());
		ZCLType<arrayType> zclConverter;
		for (std::string singleRawData : raw) {
			std::vector<uint8_t> singleResult { zclConverter.getRaw(singleRawData) };
			std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(result));
		}
		return result;
	}
	std::vector<uint8_t> getRaw(uint64_t) const override {
		return std::vector<uint8_t> { };
	}

	virtual ZCLTypeDataType getZCLDataType() const override {
		return ZCLTypeDataType::ZCLTypeArray;
	}
};

template<ZCLTypeDataType arrayType>
class ZCLCmdList: public ZCLTypeBase {
public:
	std::vector<uint8_t> getRaw(const std::string &) const override {
		return std::vector<uint8_t> { };
	}
	std::vector<uint8_t> getRaw(const std::vector<std::string> & raw) const override {
		std::vector<uint8_t> result;

		ZCLType<arrayType> zclConverter;
		for (std::string singleRawData : raw) {
			std::vector<uint8_t> singleResult { zclConverter.getRaw(singleRawData) };
			std::copy(singleResult.begin(), singleResult.end(), std::back_inserter(result));
		}
		return result;
	}
	std::vector<uint8_t> getRaw(uint64_t) const override {
		return std::vector<uint8_t> { };
	}

	virtual ZCLTypeDataType getZCLDataType() const override {
		return ZCLTypeDataType::ZCLTypeArray;
	}
};

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeStringChar>::getRaw(const std::string & value) const {
	std::vector<uint8_t> result;
	result.push_back(value.length());
	for (unsigned int i = 0; i < value.length(); ++i) {
		result.push_back(value[i]);
	}
	return result;
}

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeIEEEaddress>::getRaw(const std::vector<std::string> &octets) const {
	std::vector<uint8_t> result;

	for (std::string strOctet : octets) {
		uint8_t octect = strtol(strOctet.c_str(), NULL, 16);
		result.push_back(octect);
	}
	return result;
}

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeIEEEaddress>::getRaw(const std::string &octets) const {
	std::vector<uint8_t> result;
	char octet[3] = { 0, 0, 0 };

	for (int i = 0; i < 7; i++) {
		if ((octets[3 * i + 2] != '-') && (octets[3 * i + 2] != ':')) {
			throw boost::bad_lexical_cast();
		}
	}
	for (int i = 0; i < 8; i++) {
		octet[0] = octets[3 * i];
		octet[1] = octets[3 * i + 1];
		if (!isxdigit(octet[0]) || !isxdigit(octet[1])) {
			throw boost::bad_lexical_cast();
		}
		result.push_back(std::stoi(octet, 0, 16));
	}

	return result;
}

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeUInt16>::getRaw(uint64_t value) const {
	std::vector<uint8_t> result;
	result.push_back(value & 0xFF);
	result.push_back((value >> 8) & 0xFF);
	return result;
}

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeUInt16>::getRaw(const std::string & value) const {
	uint32_t data = boost::lexical_cast<uint32_t>(value);
	return getRaw(data);
}

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeUInt8>::getRaw(uint64_t value) const {
	std::vector<uint8_t> result;
	result.push_back(value & 0xFF);
	return result;
}

template<>
inline std::vector<uint8_t> ZCLType<ZCLTypeDataType::ZCLTypeUInt8>::getRaw(const std::string & value) const {
	uint32_t data = boost::lexical_cast<uint32_t>(value);
	return getRaw(data);
}

inline std::ostream & operator <<(std::ostream & out, ZCLTypeDataType type){
	const auto found = names.find(type);
	if (found != names.end() ){
		out << found->second;
	} else {
		out << "unknow type: ";
	}
	out << " (" << static_cast<int>(type) << ")";

	return out;
}

#endif /* ZCLTypeDATATYPE_H_ */
