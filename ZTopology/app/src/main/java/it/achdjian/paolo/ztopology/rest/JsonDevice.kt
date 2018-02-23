package it.achdjian.paolo.ztopology.domusEngine.rest

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
data class JsonDevice(
    var short_address: String,
    var extended_address: String,
    var capability: Int,
    var endpoints: Map<Int, String>
) {
    constructor() : this("0", "", 0, hashMapOf()) {
    }
}

class Device(json: JsonDevice) {
    val networkId: Int
    val extendAddr: String
    val capability: Int
    val endpoints: List<Int>

    init {
        networkId = json.short_address.toInt(16)
        extendAddr = json.extended_address
        capability = json.capability
        endpoints = json.endpoints.map { it.value.toInt(16) }
    }
}