package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import com.fasterxml.jackson.annotation.JsonCreator
import com.fasterxml.jackson.annotation.JsonProperty

/**
 * Created by Paolo Achdjian on 10/31/17.
 */
data class TemperatureDataJSON @JsonCreator(mode = JsonCreator.Mode.PROPERTIES) constructor(
        @JsonProperty("network_id") var networkId: Int,
        @JsonProperty("value") var temperature: Int,
        @JsonProperty("time")var time: String?){
}