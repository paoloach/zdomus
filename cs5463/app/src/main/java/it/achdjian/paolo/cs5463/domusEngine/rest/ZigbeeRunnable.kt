package it.achdjian.paolo.cs5463.domusEngine.rest

import com.fasterxml.jackson.databind.ObjectMapper

/**
 * Created by Paolo Achdjian on 7/12/17.
 */
abstract class ZigbeeRunnable : Runnable {
    companion object {
        val MAPPER = ObjectMapper()
        val TAG="ZIGBEE COM"
    }
}