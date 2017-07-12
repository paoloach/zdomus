package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.os.Handler
import android.util.Log
import com.fasterxml.jackson.databind.ObjectMapper
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpoint
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetEndpoint(val nwkAddress: Int, val endpoint: Int, val domusEngineRest: DomusEngineRest) : ZigbeeRunnable() {

    override fun run() {
        val body = domusEngineRest.get("/devices/$nwkAddress/endpoint/$endpoint")
        if (body.isNotBlank()) {
            try {
                val zEndpoint = MAPPER.readValue(body, ZEndpoint::class.java)
                val handler = Handler()
                handler.sendMessage(handler.obtainMessage(MessageType.NEW_ENDPOINT,zEndpoint))
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$nwkAddress/endpoint/$endpoint")
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}