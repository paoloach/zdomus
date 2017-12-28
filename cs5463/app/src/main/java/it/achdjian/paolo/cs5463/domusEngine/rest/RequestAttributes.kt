package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import it.achdjian.paolo.cs5463.domusEngine.AttributeCoord
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.MessageType
import java.io.IOException

/**
 * Created by Paolo Achdjian on 18/05/16.
 */
class RequestAttributes(val coord: AttributeCoord) : ZigbeeRunnable() {

    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(coord.networkdId, 16)).
                append("/endpoint/").
                append(Integer.toString(coord.endpointId, 16)).
                append("/cluster/in/").
                append(Integer.toString(coord.clusterId, 16)).
                append("/attributes?id=").
                append(coord.attributeId.toString(16))
        Log.d(TAG, builder.toString())
        val body = DomusEngineRest.get(builder.toString())
        if (body.isNotBlank()) {
            try {
                val jsonAttributes = MAPPER.readValue<List<JSonAttribute>>(body, object : TypeReference<List<JSonAttribute>>() {})
                val attributes = Attributes(coord.networkdId, coord.endpointId, coord.clusterId, jsonAttributes)
                DomusEngine.handler.sendMessage(DomusEngine.handler.obtainMessage(MessageType.NEW_ATTRIBUTES, attributes))
            }catch (e: IOException) {
                Log.e(TAG, "Error parsing response for ${coord}", e)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}
