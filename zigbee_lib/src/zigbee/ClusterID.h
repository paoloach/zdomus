/*
 * ClusterID.h
 *
 *  Created on: 07/mag/2015
 *      Author: Paolo Achdjian
 */

#ifndef SRC_ZIGBEE_CLUSTERID_H_
#define SRC_ZIGBEE_CLUSTERID_H_

#include "../zcl/ClustersEnum.h"
#include <zigbee/ZigbeeTypes.h>

#include <string>
#include <boost/lexical_cast.hpp>
#include <ostream>
#include <istream>

namespace zigbee {

class ClusterID {
public:
	constexpr ClusterID():clusterID(0) {
	}

	explicit constexpr ClusterID(int clusterID):clusterID(clusterID) {
	}


	explicit ClusterID(const std::string & clusterSrc):clusterID( boost::lexical_cast<int>(clusterSrc) ) {
	}

	constexpr ClusterID(const ClusterID & other):clusterID(other.clusterID) {
	}

	bool operator==(const ClusterID other) const {
		return clusterID == other.clusterID;
	}

	bool operator==(int other) const {
		return clusterID == other;
	}

	bool operator<(const ClusterID other) const {
		return clusterID < other.clusterID;
	}

	bool operator<(int other) const {
		return clusterID < other;
	}

	ZigbeeClusterId getId() const {
		return clusterID;
	}

	void setId(int id) {
		clusterID = id;
	}

	friend std::ostream & operator<<(std::ostream & out, const ClusterID & clusterId);
	friend std::istream & operator>>( std::istream & in, ClusterID & clusterId);
private:
	int clusterID;
};

inline std::ostream & operator<<(std::ostream & out, const ClusterID & clusterId){
	out << clusterId.clusterID;
	return out;
}

inline std::istream & operator>>( std::istream & in, ClusterID & clusterId){
	in >> clusterId.clusterID;
	return in;
}

extern ClusterID BasicClusterID;
extern ClusterID PowerConfigurationClusterID;
extern ClusterID DeviceTemperatureConfigClusterID;
extern ClusterID IdentifyClusetrID;
extern ClusterID GroupsClusterID;
extern ClusterID SceneClusterID;
extern ClusterID OnOffClusterID;
extern ClusterID OnOffConfID;
extern ClusterID LevelControClusterID;
extern ClusterID AlarmsID;
extern ClusterID TimeID;
extern ClusterID RSSILocationID;
extern ClusterID AnalogInputBasicID;
extern ClusterID AnalogOutputBasicID;
extern ClusterID AnalogValBasicID;
extern ClusterID BinaryInputBasicID;
extern ClusterID BinaryOutputBasicID;
extern ClusterID BinaryValueBasicID;
extern ClusterID MultistateInputBasicID;
extern ClusterID MultistateOutputBasicID;
extern ClusterID MultistateValueBasicID;
extern ClusterID CommissioningID;
extern ClusterID IlluminanceMeasureID;
extern ClusterID IlluminanceLevelSensingID;
extern ClusterID TemperatureMeasurementID;
extern ClusterID PressureMeasurementID;
extern ClusterID FlowMeasurementID;
extern ClusterID RelativeHumidityMeasurementID;
extern ClusterID OccupancySensingID;
extern ClusterID Metering;
extern ClusterID ElectricalMeasurament;

} /* namespace zigbee */

#endif /* SRC_ZIGBEE_CLUSTERID_H_ */
