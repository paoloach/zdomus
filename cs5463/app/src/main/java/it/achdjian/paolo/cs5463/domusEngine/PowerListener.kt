package it.achdjian.paolo.cs5463.domusEngine

import it.achdjian.paolo.cs5463.zigbee.PowerNode

/**
 * Created by Paolo Achdjian on 8/25/17.
 */
interface PowerListener {
    fun newPower( powerNode: PowerNode)
}