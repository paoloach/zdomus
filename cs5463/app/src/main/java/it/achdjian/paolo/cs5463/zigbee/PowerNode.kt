package it.achdjian.paolo.cs5463.zigbee

import it.achdjian.paolo.cs5463.domusEngine.rest.JSonPowerNode

/**
 * Created by Paolo Achdjian on 9/14/17.
 */

class PowerNode constructor(json: JSonPowerNode) {
    val error: Boolean
    val nwkId: Int
    val powerLevel: String
    val powerMode: String
    val availablePowerSource: Int
    val currentPowerSource: Int

    init {
        error = json.error
        nwkId = json.nwkId.toInt(16)
        powerLevel = json.powerLevel
        powerMode = json.powerMode
        availablePowerSource = json.availablePowerSource
        currentPowerSource = json.currentPowerSource
    }
}