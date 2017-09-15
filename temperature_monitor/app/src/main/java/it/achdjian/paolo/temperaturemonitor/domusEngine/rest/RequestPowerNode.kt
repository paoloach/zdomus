package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.zigbee.PowerNode
import java.io.IOException

/**
 * Created by Paolo Achdjian on 8/25/17.
 */
class RequestPowerNode(val networkdId: Int, val domusEngineRest: DomusEngineRest, val domusEngine: DomusEngine) : ZigbeeRunnable() {
    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(networkdId, 16)).
                append("/power")
        Log.d(TAG, builder.toString())
        val body = domusEngineRest.get(builder.toString())
        if (body.isNotBlank()) {
            try {
                Log.d(TAG, "Power node response: " )
                val jsonPowerNode = MAPPER.readValue<JSonPowerNode>(body, object : TypeReference<JSonPowerNode>() {})
                val powerNode = PowerNode(jsonPowerNode)
                domusEngine.handler.sendMessage(domusEngine.handler.obtainMessage(MessageType.NEW_POWER, powerNode))
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for powernode of device ${networkdId}", e)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}