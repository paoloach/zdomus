package it.achdjian.paolo.temperaturemonitor.zigbee

import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.JsonDevice

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class ZDevice(val shortAddress: Int, val extendedAddr: String, val capabilities: Int) {
    val endpoints: MutableMap<Int, ZEndpoint?> = HashMap()

    constructor(json: JsonDevice):this(json.short_address, json.extended_address, json.capability){
        for (value in json.endpoints.values) {
            endpoints.put(Integer.parseInt(value, 16),null)
        }
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