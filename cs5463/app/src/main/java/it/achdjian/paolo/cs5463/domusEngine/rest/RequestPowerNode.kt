package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.MessageType
import it.achdjian.paolo.cs5463.zigbee.PowerNode
import java.io.IOException

/**
 * Created by Paolo Achdjian on 8/25/17.
 */
class RequestPowerNode(val networkdId: Int) : ZigbeeRunnable() {
    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(networkdId, 16)).
                append("/power")
        Log.d(TAG, builder.toString())
        val body = DomusEngineRest.get(builder.toString())
        if (body.isNotBlank()) {
            try {
                Log.d(TAG, "Power node response: " )
                val jsonPowerNode = MAPPER.readValue<JSonPowerNode>(body, object : TypeReference<JSonPowerNode>() {})
                val powerNode = PowerNode(jsonPowerNode)
                DomusEngine.handler.sendMessage(DomusEngine.handler.obtainMessage(MessageType.NEW_POWER, powerNode))
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for powernode of device ${networkdId}", e)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
}