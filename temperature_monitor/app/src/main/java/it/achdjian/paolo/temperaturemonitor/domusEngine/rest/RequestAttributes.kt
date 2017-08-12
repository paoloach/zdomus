package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import it.achdjian.paolo.temperaturemonitor.domusEngine.AttributeCoord
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import java.io.IOException

/**
 * Created by Paolo Achdjian on 18/05/16.
 */
class RequestAttributes(val coord: AttributeCoord, val domusEngineRest: DomusEngineRest, val domusEngine: DomusEngine) : ZigbeeRunnable() {

    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(coord.networkdId, 16)).
                append("/endpoint/").
                append(Integer.toString(coord.endpointId, 16)).
                append("/cluster/in/").
                append(Integer.toString(coord.clusterId, 16)).
                append("/attributes?id=").
                append(coord.attributeId)
        Log.d(TAG, builder.toString())
        val body = domusEngineRest.get(builder.toString())
        if (body.isNotBlank()) {
            try {
                val jsonAttributes = MAPPER.readValue<List<JSonAttribute>>(body, object : TypeReference<List<JSonAttribute>>() {})
                val attributes = Attributes(coord.networkdId, coord.endpointId, coord.clusterId, jsonAttributes)
                domusEngine.handler.sendMessage(domusEngine.handler.obtainMessage(MessageType.NEW_ATTRIBUTES, attributes))
            }catch (e: IOException) {
                Log.e(TAG, "Error parsing response for ${coord}", e)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}
