package it.achdjian.paolo.ztopology.domusEngine.rest

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
data class JsonDevice(var short_address: Int, var extended_address: String, var capability: Int, var endpoints: Map<Int, String>) {
    constructor() : this(0, "", 0, hashMapOf()) {
    }
}