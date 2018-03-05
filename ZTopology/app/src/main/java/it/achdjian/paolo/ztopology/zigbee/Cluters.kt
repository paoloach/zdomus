package it.achdjian.paolo.ztopology.zigbee


enum class Cluster(val id: Int) {
    UNKNOWN(-1),
    BASIC_CLUSTER(0),
    POWER_CONFIGURATION_CLUSTER(1),
    DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER(2),
    IDENTIFY_CLUSTER(3),
    GROUPS_CLUSTER(4),
    SCENES_CLUSTER(5),
    ON_OFF_CLUSTER(6),
    ON_OFF_SWITCH_CONFIGURATION_CLUSTER(7),
    LEVEL_CONTROL(8),
    ALARMS(9),
    TIME(0x0A),
    RSSI_LOCATION(0x0B),
    ANALOG_INPUT(0x0C),
    ANALOG_OUTPUT(0x0D),
    ANALOG_VALUE(0x0E),
    BINARY_INPUT(0x0F),
    BINARY_OUTPUT(0x10),
    BINARY_VALUE(0x11),
    MULTISTATE_INPUT(0x12),
    MULTISTATE_OUTPUT(0x13),
    MULTISTATE_VALUE(0x14),
    COMMISSIONING(0x15),
    SHADE_CONFIGURATION(0x100),
    DOOR_LOCK(0x101),
    PUMP_CONFIGURATION(0x200),
    THERMOSTAT(0x201),
    FAN_CONTROL(0x202),
    DEHUMIDIFICATION(0x203),
    THERMOSTAT_UI_CONF(0x204),
    COLOR_CONTROL(0x300),
    BALLAST_CONF(0x301),
    ILLUMINANCE_MEASURE(0x0400),
    ILLUMINCANCE_LEVEL_SENSING(0x0401),
    TEMPERATURE_MEASUREMENT(0x0402),
    PRESSURE_MEASUREMENT(0x0403),
    FLOW_MEASUREMENT(0x0404),
    HUMIDITY_MEASUREMENT(0x0405),
    OCCUPANCY_SENSOR(0x0406),
    IAS_ZONE(0x500),
    IAS_ACE(0x501),
    IAS_WD(0x502);


}

/**
 * Created by Paolo Achdjian on 2/26/18.
 */
fun clusterToString(clusterId: Int): String {

    val cluster = Cluster.values().firstOrNull { it.id==clusterId };
    if (cluster !=null)
        return cluster.name
    return "Unknown"
}

fun idToCluster(clusterId: Int):Cluster {
    val cluster = Cluster.values().firstOrNull { it.id==clusterId };
    if (cluster !=null)
        return cluster
    return Cluster.UNKNOWN
}