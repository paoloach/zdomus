package it.achdjian.paolo.ztopology.zigbee

import it.achdjian.paolo.ztopology.domusEngine.rest.JsonDevice
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint


/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class ZDevice(val shortAddress: Int, val extendedAddr: String, val capabilities: Int) {

    val endpoints: MutableMap<Int, ZEndpoint?> = HashMap()

    constructor(json: JsonDevice) : this(json.short_address, json.extended_address, json.capability) {
        json.endpoints.values.forEach({ endpoints.put(Integer.parseInt(it, 16), null) })
    }

    fun hasEndpoint(endpoint: Int): Boolean {
        for (containedEndpoint in endpoints.keys) {
            if (containedEndpoint == endpoint && endpoints[endpoint] != null) {
                return true
            }
        }
        return false
    }
}

val nullZDevice = ZDevice(0,"00:00:00:00::00:00:00:00",0)