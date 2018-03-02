package it.achdjian.paolo.ztopology.zigbee

/**
 * Created by paolo on 14/04/16.
 */
object Constants {
    var DOMUS_ENGINE_ADDRESS = "DomusEngineAddress"

    val ZCL_HA_DEVICEID_ON_OFF_SWITCH = 0x0000
    val ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH = 0x0001
    val ZCL_HA_DEVICEID_ON_OFF_OUTPUT = 0x0002
    val ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT = 0x0003
    val ZCL_HA_DEVICEID_SCENE_SELECTOR = 0x0004
    val ZCL_HA_DEVICEID_CONFIGURATION_TOOL = 0x0005
    val ZCL_HA_DEVICEID_REMOTE_CONTROL = 0x0006
    val ZCL_HA_DEVICEID_COMBINED_INTERFACE = 0x0007
    val ZCL_HA_DEVICEID_RANGE_EXTENDER = 0x0008
    val ZCL_HA_DEVICEID_MAINS_POWER_OUTLET = 0x0009
    val ZCL_HA_DEVICEID_DOOR_LOCK = 0x000A
    val ZCL_HA_DEVICEID_DOOR_LOCK_CONTROLLER = 0x000B
    val ZCL_HA_DEVICEID_SIMPLE_SENSOR = 0x000C
    val ZCL_HA_DEVICEID_CONSUMPTION_AWARENESS_DEVICE = 0x000D
    val ZCL_HA_DEVICEID_HOME_GATEWAY = 0x0050
    val ZCL_HA_DEVICEID_SMART_PLUG = 0x0051
    val ZCL_HA_DEVICEID_WHITE_GOODS = 0x0052
    val ZCL_HA_DEVICEID_METER_INTERACE = 0x0053
    // This is a reserved value which could be used for test purposes
    val ZCL_HA_DEVICEID_TEST_DEVICE = 0x00FF
    // Lighting Device IDs
    val ZCL_HA_DEVICEID_ON_OFF_LIGHT = 0x0100
    val ZCL_HA_DEVICEID_DIMMABLE_LIGHT = 0x0101
    val ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT = 0x0102
    val ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH = 0x0103
    val ZCL_HA_DEVICEID_DIMMER_SWITCH = 0x0104
    val ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH = 0x0105
    val ZCL_HA_DEVICEID_LIGHT_SENSOR = 0x0106
    val ZCL_HA_DEVICEID_OCCUPANCY_SENSOR = 0x0107
    // Closures Device IDs
    val ZCL_HA_DEVICEID_SHADE = 0x0200
    val ZCL_HA_DEVICEID_SHADE_CONTROLLER = 0x0201
    val ZCL_HA_DEVICEID_WINDOW_COVERING_DEVICE = 0x0202
    val ZCL_HA_DEVICEID_WINDOW_COVERING_CONTROLLER = 0x0203
    // HVAC Device IDs
    val ZCL_HA_DEVICEID_HEATING_COOLING_UNIT = 0x0300
    val ZCL_HA_DEVICEID_THERMOSTAT = 0x0301
    val ZCL_HA_DEVICEID_TEMPERATURE_SENSOR = 0x0302
    val ZCL_HA_DEVICEID_PUMP = 0x0303
    val ZCL_HA_DEVICEID_PUMP_CONTROLLER = 0x0304
    val ZCL_HA_DEVICEID_PRESSURE_SENSOR = 0x0305
    val ZCL_HA_DEVICEID_FLOW_SENSOR = 0x0306
    val ZCL_HA_DEVICEID_MINI_SPLIT_AC = 0x0307
    // public static final intruder Alarm Systems (IAS) Device IDs
    val ZCL_HA_DEVICEID_IAS_CONTROL_INDICATING_EQUIPMENT = 0x0400
    val ZCL_HA_DEVICEID_IAS_ANCILLARY_CONTROL_EQUIPMENT = 0x0401
    val ZCL_HA_DEVICEID_IAS_ZONE = 0x0402
    val ZCL_HA_DEVICEID_IAS_WARNING_DEVICE = 0x0403

    val BASIC_CLUSTER = 0
    val POWER_CONFIGURATION_CLUSTER = 1
    val DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER = 2
    val IDENTIFY_CLUSTER = 3
    val GROUPS_CLUSTER = 4
    val SCENES_CLUSTER = 5
    val ON_OFF_CLUSTER = 6
    val ON_OFF_SWITCH_CONFIGURATION_CLUSTER = 7
    val LEVEL_CONTROL=8
    val ALARMS=9
    val TIME=0x0A
    val RSSI_LOCATION=0x0B
    val ANALOG_INPUT=0x0C
    val ANALOG_OUTPUT=0x0D
    val ANALOG_VALUE=0x0E
    val BINARY_INPUT=0x0F
    val BINARY_OUTPUT=0x10
    val BINARY_VALUE=0x11
    val MULTISTATE_INPUT=0x12
    val MULTISTATE_OUTPUT=0x13
    val MULTISTATE_VALUE=0x14
    val COMMISSIONING=0x15
    val SHADE_CONFIGURATION=0x100
    val DOOR_LOCK=0x101
    val PUMP_CONFIGURATION=0x200
    val THERMOSTAT=0x201
    val FAN_CONTROL=0x202
    val DEHUMIDIFICATION = 0x203
    val THERMOSTAT_UI_CONF=0x204
    val COLOR_CONTROL=0x300
    val BALLAST_CONF=0x301
    val ILLUMINANCE_MEASURE = 0x0400
    val ILLUMINCANCE_LEVEL_SENSING = 0x0401
    val TEMPERATURE_MEASUREMENT = 0x0402
    val PRESSURE_MEASUREMENT = 0x0403
    val FLOW_MEASUREMENT = 0x0404
    val HUMIDITY_MEASUREMENT = 0x0405
    val OCCUPANCY_SENSOR = 0x0406
    val IAS_ZONE=0x500
    val IAS_ACE=0x501
    val IAS_WD=0x502



    // BASIC CLUSTER ATTRIBUTES
    val ZCL_VERSION = 0
    val APPLICATION_VERSION = 1
    val STACK_VERSION = 2
    val HW_VERSION = 3
    val MANUFACTURER_NAME = 4
    val MODEL_IDENTIFIER = 5
    val DATE_CODE = 6
    val POWER_SOURCE = 7
    val LOCATION_DESCRIPTION = 0x10
    val PHYSICAL_ENVIRONMENT = 0x11
    val DEVICE_ENABLED = 0x12
    val ALARM_MASK = 0x13
    val DISABLE_LOCAL_CONFIG = 0x14



}
