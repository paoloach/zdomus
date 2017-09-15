package it.achdjian.paolo.temperaturemonitor.domusEngine

import it.achdjian.paolo.temperaturemonitor.zigbee.PowerNode

/**
 * Created by Paolo Achdjian on 8/25/17.
 */
interface PowerListener {
    fun newPower( powerNode: PowerNode)
}