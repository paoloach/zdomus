package it.achdjian.paolo.domusviewer;

/**
 * Created by paolo on 14/04/16.
 */
public class Constants {
    public static String DOMUS_ENGINE_ADDRESS = "DomusEngineAddress";

    public static final int ZCL_HA_DEVICEID_ON_OFF_SWITCH = 0x0000;
    public static final int ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH = 0x0001;
    public static final int ZCL_HA_DEVICEID_ON_OFF_OUTPUT = 0x0002;
    public static final int ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT = 0x0003;
    public static final int ZCL_HA_DEVICEID_SCENE_SELECTOR = 0x0004;
    public static final int ZCL_HA_DEVICEID_CONFIGURATION_TOOL = 0x0005;
    public static final int ZCL_HA_DEVICEID_REMOTE_CONTROL = 0x0006;
    public static final int ZCL_HA_DEVICEID_COMBINED_INTERFACE = 0x0007;
    public static final int ZCL_HA_DEVICEID_RANGE_EXTENDER = 0x0008;
    public static final int ZCL_HA_DEVICEID_MAINS_POWER_OUTLET = 0x0009;
    public static final int ZCL_HA_DEVICEID_DOOR_LOCK = 0x000A;
    public static final int ZCL_HA_DEVICEID_DOOR_LOCK_CONTROLLER = 0x000B;
    public static final int ZCL_HA_DEVICEID_SIMPLE_SENSOR = 0x000C;
    public static final int ZCL_HA_DEVICEID_CONSUMPTION_AWARENESS_DEVICE = 0x000D;
    public static final int ZCL_HA_DEVICEID_HOME_GATEWAY = 0x0050;
    public static final int ZCL_HA_DEVICEID_SMART_PLUG = 0x0051;
    public static final int ZCL_HA_DEVICEID_WHITE_GOODS = 0x0052;
    public static final int ZCL_HA_DEVICEID_METER_INTERACE=0x0053;
// This is a reserved value which could be used for test purposes
    public static final int ZCL_HA_DEVICEID_TEST_DEVICE = 0x00FF;
// Lighting Device IDs
    public static final int ZCL_HA_DEVICEID_ON_OFF_LIGHT = 0x0100;
    public static final int ZCL_HA_DEVICEID_DIMMABLE_LIGHT = 0x0101;
    public static final int ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT = 0x0102;
    public static final int ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH = 0x0103;
    public static final int ZCL_HA_DEVICEID_DIMMER_SWITCH = 0x0104;
    public static final int ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH = 0x0105;
    public static final int ZCL_HA_DEVICEID_LIGHT_SENSOR = 0x0106;
    public static final int ZCL_HA_DEVICEID_OCCUPANCY_SENSOR = 0x0107;
// Closures Device IDs
    public static final int ZCL_HA_DEVICEID_SHADE = 0x0200;
    public static final int ZCL_HA_DEVICEID_SHADE_CONTROLLER = 0x0201;
    public static final int ZCL_HA_DEVICEID_WINDOW_COVERING_DEVICE = 0x0202;
    public static final int ZCL_HA_DEVICEID_WINDOW_COVERING_CONTROLLER = 0x0203;
// HVAC Device IDs
    public static final int ZCL_HA_DEVICEID_HEATING_COOLING_UNIT = 0x0300;
    public static final int ZCL_HA_DEVICEID_THERMOSTAT = 0x0301;
    public static final int ZCL_HA_DEVICEID_TEMPERATURE_SENSOR = 0x0302;
    public static final int ZCL_HA_DEVICEID_PUMP = 0x0303;
    public static final int ZCL_HA_DEVICEID_PUMP_CONTROLLER = 0x0304;
    public static final int ZCL_HA_DEVICEID_PRESSURE_SENSOR = 0x0305;
    public static final int ZCL_HA_DEVICEID_FLOW_SENSOR = 0x0306;
    public static final int ZCL_HA_DEVICEID_MINI_SPLIT_AC = 0x0307;
// public static final intruder Alarm Systems (IAS) Device IDs
    public static final int ZCL_HA_DEVICEID_IAS_CONTROL_INDICATING_EQUIPMENT = 0x0400;
    public static final int ZCL_HA_DEVICEID_IAS_ANCILLARY_CONTROL_EQUIPMENT = 0x0401;
    public static final int ZCL_HA_DEVICEID_IAS_ZONE = 0x0402;
    public static final int ZCL_HA_DEVICEID_IAS_WARNING_DEVICE = 0x0403;

    public static final int BASIC_CLUSTER =0;
    public static final int POWER_CONFIGURATION_CLUSTER=1;
    public static final int DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER=2;
    public static final int IDENTIFY_CLUSTER=3;
    public static final int GROUP_CLUSTER=4;
    public static final int SCENES_CLUSTER=5;
    public static final int ON_OFF_CLUSTER=6;
    public static final int ON_OFF_SWITCH_CONFIGURATION_CLUSTER=7;
}
