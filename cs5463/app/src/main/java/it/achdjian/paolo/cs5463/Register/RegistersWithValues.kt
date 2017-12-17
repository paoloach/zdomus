package it.achdjian.paolo.cs5463.Register

/**
 * Created by Paolo Achdjian on 11/22/17.
 */
enum class RegistersWithValues(val label: String, val index:Int ) {
    CURRENT_DC_OFFSET("Current DC offset", 1),
    CURRENT_GAIN("Current Gain",2),
    VOLTAGE_DC_OFFSET("Voltage DC offset", 3),
    VOLTAGE_GAIN("Voltage gain", 4),
    CURRENT_AC_OFFSET("Current AC offset", 16),
    VOLTAGE_AC_OFFSET("Voltage AC offset", 17),
    CURRENT_INSTANTANEUS("Current instantaneus", 7),
    VOLTAGE_INSTANTANEUS("Voltage instantaneus", 8),
    POWER_INSTANTANEUS("Power instantaneus", 9),
    ACTIVE_POWER("Real power", 10),
    RMS_CURRENT("RMS current", 11),
    RMS_VOLTAGE("RMS voltage", 12),
    REACTIVE_POWER_AVERAGE("Average reactive power", 20),
    INSTANTANEOUS_REACTIVE_POWER("Instantaneous reactive power", 21),
    PEAK_CURRENT("Peak current", 22),
    PEAK_VOLTAGE("Peak voltage", 23)
}