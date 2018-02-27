package it.achdjian.paolo.ztopology.zigbee

import it.achdjian.paolo.ztopology.zigbee.Constants.BASIC_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.FLOW_MEASUREMENT
import it.achdjian.paolo.ztopology.zigbee.Constants.GROUP_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.HUMIDITY_MEASUREMENT
import it.achdjian.paolo.ztopology.zigbee.Constants.IDENTIFY_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.ILLUMINANCE_MEASURE
import it.achdjian.paolo.ztopology.zigbee.Constants.ILLUMINCANCE_LEVEL_SENSING
import it.achdjian.paolo.ztopology.zigbee.Constants.OCCUPANCY_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ON_OFF_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.ON_OFF_SWITCH_CONFIGURATION_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.POWER_CONFIGURATION_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.PRESSURE_MEASUREMENT
import it.achdjian.paolo.ztopology.zigbee.Constants.SCENES_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.TEMPERATURE_MEASUREMENT

/**
 * Created by Paolo Achdjian on 2/26/18.
 */
fun clusterToString(clusterId: Int): String {
    when(clusterId){
        BASIC_CLUSTER -> return "Basic"
        POWER_CONFIGURATION_CLUSTER -> return "Power Conf."
        DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER -> return "Temp. Conf."
        IDENTIFY_CLUSTER -> return "Identify"
        GROUP_CLUSTER -> return "Group"
        SCENES_CLUSTER -> return "Scene"
        ON_OFF_CLUSTER ->return "On/Off"
        ON_OFF_SWITCH_CONFIGURATION_CLUSTER -> return  "On/Off switch conf."
        ILLUMINANCE_MEASURE -> return "Illuminance"
        ILLUMINCANCE_LEVEL_SENSING -> return "Illuminance level"
        TEMPERATURE_MEASUREMENT -> return "Temperature"
        PRESSURE_MEASUREMENT-> return "Pressure"
        FLOW_MEASUREMENT -> return "Flow"
        HUMIDITY_MEASUREMENT -> return "Humidity"
        OCCUPANCY_SENSOR -> return "Occupancy"

    }
    return clusterId.toString(16)
}