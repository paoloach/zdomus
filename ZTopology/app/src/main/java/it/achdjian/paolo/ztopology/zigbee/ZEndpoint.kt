package it.achdjian.paolo.ztopology.zigbee

import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_COMBINED_INTERFACE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_CONFIGURATION_TOOL
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_CONSUMPTION_AWARENESS_DEVICE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_DIMMABLE_LIGHT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_DIMMER_SWITCH
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_DOOR_LOCK
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_DOOR_LOCK_CONTROLLER
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_FLOW_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_HEATING_COOLING_UNIT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_HOME_GATEWAY
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_IAS_ANCILLARY_CONTROL_EQUIPMENT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_IAS_CONTROL_INDICATING_EQUIPMENT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_IAS_WARNING_DEVICE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_IAS_ZONE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_LIGHT_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_MAINS_POWER_OUTLET
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_METER_INTERACE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_MINI_SPLIT_AC
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_OCCUPANCY_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_ON_OFF_LIGHT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_ON_OFF_OUTPUT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_ON_OFF_SWITCH
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_PRESSURE_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_PUMP
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_PUMP_CONTROLLER
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_RANGE_EXTENDER
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_REMOTE_CONTROL
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_SCENE_SELECTOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_SHADE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_SHADE_CONTROLLER
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_SIMPLE_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_SMART_PLUG
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_TEST_DEVICE
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_THERMOSTAT
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_WHITE_GOODS
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_WINDOW_COVERING_CONTROLLER
import it.achdjian.paolo.ztopology.zigbee.Constants.ZCL_HA_DEVICEID_WINDOW_COVERING_DEVICE
import java.io.Serializable
import java.util.HashMap
import kotlin.collections.ArrayList

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
data class ZEndpointJSon(
    val short_address: String,
    val endpoint_id: String,
    val profile_id: Int,
    val device_id: Int,
    val device_version: Int
) {
    constructor() : this("0", "0", 0, 0, 0)

    var input_clusters: Map<Int, String> = HashMap()
    var output_clusters: Map<Int, String> = HashMap()
}

data class ZEndpoint(
    val networkAddress: Int,
    val endpointId: Int,
    val profileId: Int,
    val deviceId: Int,
    val deviceVersion: Int
) : Serializable {
    constructor(endpoint: ZEndpointJSon) : this(
        endpoint.short_address.toInt(16),
        endpoint.endpoint_id.toInt(16),
        endpoint.profile_id, endpoint.device_id, endpoint.device_version
    ) {
        inCluster = endpoint.input_clusters.map { idToCluster(it.value.toInt(16)) }
        outCluster = endpoint.output_clusters.map { idToCluster(it.value.toInt(16)) }
    }


    var inCluster: List<Cluster> = ArrayList()
    var outCluster: List<Cluster> = ArrayList()
}

fun deviceIdName(deviceId: Int): String {
    when (deviceId) {
        ZCL_HA_DEVICEID_ON_OFF_SWITCH -> return "On/Off switch"
        ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH -> return "Level Control switch"
        ZCL_HA_DEVICEID_ON_OFF_OUTPUT -> return "on/off output"
        ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT -> return "level controllable output"
        ZCL_HA_DEVICEID_SCENE_SELECTOR -> return "scene selector"
        ZCL_HA_DEVICEID_CONFIGURATION_TOOL -> return "configuration"
        ZCL_HA_DEVICEID_REMOTE_CONTROL -> return "remote controller"
        ZCL_HA_DEVICEID_COMBINED_INTERFACE -> return "combined"
        ZCL_HA_DEVICEID_RANGE_EXTENDER -> return "range extender"
        ZCL_HA_DEVICEID_MAINS_POWER_OUTLET -> return "mains power outlet"
        ZCL_HA_DEVICEID_DOOR_LOCK -> return "door lock"
        ZCL_HA_DEVICEID_DOOR_LOCK_CONTROLLER -> return "door lock controller"
        ZCL_HA_DEVICEID_SIMPLE_SENSOR -> return "simple sensor"
        ZCL_HA_DEVICEID_CONSUMPTION_AWARENESS_DEVICE -> return "consumption awareness"
        ZCL_HA_DEVICEID_HOME_GATEWAY -> return "home gateway"
        ZCL_HA_DEVICEID_SMART_PLUG -> return "smart plug"
        ZCL_HA_DEVICEID_WHITE_GOODS -> return "white goods"
        ZCL_HA_DEVICEID_METER_INTERACE -> return "meter interface"

        ZCL_HA_DEVICEID_TEST_DEVICE -> return "test device"
    // Lighting Device IDs
        ZCL_HA_DEVICEID_ON_OFF_LIGHT -> return "on/off ligh"
        ZCL_HA_DEVICEID_DIMMABLE_LIGHT -> return "dimmable light"
        ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT -> return "colored dimmable light"
        ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH -> return "on/off light switch"
        ZCL_HA_DEVICEID_DIMMER_SWITCH -> return "dimmer switch"
        ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH -> return "color dimmer swith"
        ZCL_HA_DEVICEID_LIGHT_SENSOR -> return "light sensor"
        ZCL_HA_DEVICEID_OCCUPANCY_SENSOR -> return "occupancy sensor"
    // Closures Device IDs
        ZCL_HA_DEVICEID_SHADE -> return "shade"
        ZCL_HA_DEVICEID_SHADE_CONTROLLER -> return "shade controoller"
        ZCL_HA_DEVICEID_WINDOW_COVERING_DEVICE -> return "covering device"
        ZCL_HA_DEVICEID_WINDOW_COVERING_CONTROLLER -> return "covering controller"

        ZCL_HA_DEVICEID_HEATING_COOLING_UNIT -> return "Heating cooling unit"
        ZCL_HA_DEVICEID_THERMOSTAT -> return "Thermostat"
        ZCL_HA_DEVICEID_TEMPERATURE_SENSOR -> return "Temperature sensor"
        ZCL_HA_DEVICEID_PUMP -> return "pump"
        ZCL_HA_DEVICEID_PUMP_CONTROLLER -> return "pump controller"
        ZCL_HA_DEVICEID_PRESSURE_SENSOR -> return "pressure sensor"
        ZCL_HA_DEVICEID_FLOW_SENSOR -> return "flow sensor"
        ZCL_HA_DEVICEID_MINI_SPLIT_AC -> return "mini split ac"
        ZCL_HA_DEVICEID_IAS_CONTROL_INDICATING_EQUIPMENT -> return "IAS Control equipment"
        ZCL_HA_DEVICEID_IAS_ANCILLARY_CONTROL_EQUIPMENT -> return "IAS Ancillary control equipment"
        ZCL_HA_DEVICEID_IAS_ZONE -> return "IAS zone"
        ZCL_HA_DEVICEID_IAS_WARNING_DEVICE -> return "IAS warning device"
    }
    return deviceId.toString(16)
}