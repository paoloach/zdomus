package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpoint
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpointJSon
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetEndpoint(val nwkAddress: Int, val endpoint_id: Int, val domusEngineRest: DomusEngineRest, val domusEngine: DomusEngine) : ZigbeeRunnable() {

    override fun run() {
        val body = domusEngineRest.get("/devices/" +nwkAddress.toString(16)+"/endpoint/" + endpoint_id.toString(16))
        if (body.isNotBlank()) {
            try {
                val endpointJson = MAPPER.readValue(body, ZEndpointJSon::class.java)
                if (endpointJson != null) {
                    val zEndpoint = ZEndpoint(endpointJson)

                    domusEngine.handler.sendMessage(domusEngine.handler.obtainMessage(MessageType.NEW_ENDPOINT, zEndpoint))
                }
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$nwkAddress/endpoint/$endpoint_id", e)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}