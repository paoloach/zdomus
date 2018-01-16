package it.achdjian.paolo.ztopology.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint
import it.achdjian.paolo.ztopology.zigbee.ZEndpointJSon
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetEndpoint(val nwkAddress: Int, val endpoint_id: Int) : ZigbeeRunnable() {

    override fun run() {
        val body = DomusEngineRest.get("/devices/" +nwkAddress.toString(16)+"/endpoint/" + endpoint_id.toString(16))
        if (body.isNotBlank()) {
            try {
                Log.i("REST", body)
                val endpointJson = MAPPER.readValue(body, ZEndpointJSon::class.java)
                if (endpointJson != null) {
                    val zEndpoint = ZEndpoint(endpointJson)
                    Log.i("REST",zEndpoint.toString())
                    DomusEngine.handler.sendMessage(DomusEngine.handler.obtainMessage(MessageType.NEW_ENDPOINT, zEndpoint))
                }
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$nwkAddress/endpoint/$endpoint_id", e)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}