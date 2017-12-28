package it.achdjian.paolo.cs5463.domusEngine.rest

import com.fasterxml.jackson.annotation.JsonCreator
import com.fasterxml.jackson.annotation.JsonProperty

/**
 * Created by Paolo Achdjian on 19/05/16.
 */
data class JSonAttribute @JsonCreator(mode = JsonCreator.Mode.PROPERTIES) constructor(
        @JsonProperty("id") var id: Int,
        @JsonProperty("name")var name: String?,
        @JsonProperty("readOnly")var readOnly: Boolean,
        @JsonProperty("type")var type: Int,
        @JsonProperty("isAvailable") var isAvailable: Boolean,
        @JsonProperty("isSupported") var isSupported: Boolean,
        @JsonProperty("status")var status: Int,
        @JsonProperty("value")var value: String?) {
    constructor() : this(0, null, false, 0, false, false, 0, null) {
    }


}

data class Attributes(val networkId: Int, val endpointId: Int, val clusterId: Int, val  jSonAttribute: List<JSonAttribute>)
