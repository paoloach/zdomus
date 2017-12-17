package it.achdjian.paolo.cs5463.domusEngine.rest

/**
 * Created by Paolo Achdjian on 8/25/17.
 */
data class JSonPowerNode(val error: Boolean, val nwkId: String, val powerLevel: String, val powerMode: String, val availablePowerSource: Int, val currentPowerSource: Int) {
    companion object {
        val MAIN_POWER = 1
        val RECHARGEABLE_BATTERY = 2
        val DISPOSABLE_BATTERY = 4
        val LEVEL_CRITICAL = "CRITICAL"
        val LEVEL_33 = "LEVEL_33"
        val LEVEL_66 = "LEVEL_66"
        val LEVEL_FULL = "LEVEL_100"
    }

    constructor() : this(true, "0", "", "", 0, 0) {}
}