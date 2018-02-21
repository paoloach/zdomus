package it.achdjian.paolo.ztopology.rest

import android.util.Log
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import java.io.IOException

/**
 * Created by Paolo Achdjian on 2/19/18.
 */
class RequestLQI(private val networkId: Int, private val index: Int) : ZigbeeRunnable() {
    override fun run() {
        Log.i(TAG, "Request LQI for " + networkId)
        val path = "/devices/${networkId.toString(16)}/lqi?index=$index"

        val body = DomusEngineRest.get(path, action = this::error)
        if (body.isNotBlank()) {
            try {
                Log.i(TAG, body)
                val nodeInfo = MAPPER.readValue(body, JsonLQI::class.java)
                DomusEngine.handler.sendMessage(
                    DomusEngine.handler.obtainMessage( MessageType.LQI_INFO, LQI(nodeInfo))
                )
                Log.i("REST", nodeInfo.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$networkId/lqi")
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }

    private fun error() = DomusEngine.sendMessage(
        MessageType.LQI_INFO_TIMEOUT,
        networkId
    )
}