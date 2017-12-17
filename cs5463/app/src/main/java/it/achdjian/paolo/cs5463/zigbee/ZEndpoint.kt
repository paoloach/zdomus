package it.achdjian.paolo.cs5463.zigbee

import java.util.HashMap

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
data class ZEndpointJSon(val short_address: String, val endpoint_id: String, val profile_id: Int, val device_id: Int, val device_version: Int) {
    constructor():this("0","0",0,0,0)
    var input_clusters: Map<Int, String> = HashMap()
    var output_clusters: Map<Int, String> = HashMap()
}

data class ZEndpoint(val short_address: Int, val endpoint_id: Int, val profile_id: Int, val device_id: Int, val device_version: Int) {
    constructor(endpoint: ZEndpointJSon) : this(
            endpoint.short_address.toInt(16),
            endpoint.endpoint_id.toInt(16),
            endpoint.profile_id, endpoint.device_id, endpoint.device_version) {
        input_clusters = endpoint.input_clusters.mapValues { it.value.toInt(16) }
        output_clusters = endpoint.output_clusters.mapValues { it.value.toInt(16) }
    }


    var input_clusters: Map<Int, Int> = HashMap()
    var output_clusters: Map<Int, Int> = HashMap()

}