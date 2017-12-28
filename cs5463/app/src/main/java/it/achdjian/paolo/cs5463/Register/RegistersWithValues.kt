package it.achdjian.paolo.cs5463.Register

/**
 * Created by Paolo Achdjian on 11/22/17.
 */
enum class RegisterType {
    TYPE_1,
    TYPE_2,
    TYPE_3
}

enum class RegistersWithValues(val label: String, val index:Int, val type: RegisterType ) {
    CURRENT_DC_OFFSET("Current DC offset", 1, RegisterType.TYPE_1),
    CURRENT_GAIN("Current Gain",2, RegisterType.TYPE_3),
    VOLTAGE_DC_OFFSET("Voltage DC offset", 3, RegisterType.TYPE_1),
    VOLTAGE_GAIN("Voltage gain", 4, RegisterType.TYPE_3),
    CURRENT_AC_OFFSET("Current AC offset", 16, RegisterType.TYPE_1),
    VOLTAGE_AC_OFFSET("Voltage AC offset", 17, RegisterType.TYPE_1),
    CURRENT_INSTANTANEUS("Current instantaneus", 7, RegisterType.TYPE_1),
    VOLTAGE_INSTANTANEUS("Voltage instantaneus", 8, RegisterType.TYPE_1),
    POWER_INSTANTANEUS("Power instantaneus", 9, RegisterType.TYPE_1),
    ACTIVE_POWER("Real power", 10, RegisterType.TYPE_1),
    RMS_CURRENT("RMS current", 11, RegisterType.TYPE_2),
    RMS_VOLTAGE("RMS voltage", 12, RegisterType.TYPE_2),
    REACTIVE_POWER_AVERAGE("Average reactive power", 20, RegisterType.TYPE_1),
    INSTANTANEOUS_REACTIVE_POWER("Instantaneous reactive power", 21, RegisterType.TYPE_1),
    PEAK_CURRENT("Peak current", 22, RegisterType.TYPE_1),
    PEAK_VOLTAGE("Peak voltage", 23, RegisterType.TYPE_1);

}