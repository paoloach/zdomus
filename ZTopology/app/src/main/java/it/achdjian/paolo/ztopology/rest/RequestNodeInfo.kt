package it.achdjian.paolo.ztopology.rest

import android.util.Log
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.JsonNodeInfo
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.NodeInfo
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import java.io.IOException

/**
 * Created by Paolo Achdjian on 2/5/18.
 */
class RequestNodeInfo(val networkId: Int) : ZigbeeRunnable() {
    override fun run() {
        Log.i(TAG, "Request children for " + networkId)
        val path = "/devices/" + networkId.toString(16) + "/node"

        val body = DomusEngineRest.get(path, action = this::error)
        if (body.isNotBlank()) {
            try {
                Log.i(TAG, body)
                val nodeInfo = MAPPER.readValue(body, JsonNodeInfo::class.java)
                DomusEngine.handler.sendMessage(
                    DomusEngine.handler.obtainMessage(
                        MessageType.NEW_NODE_INFO,
                        NodeInfo(nodeInfo)
                    )
                )
                Log.i("REST", nodeInfo.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$networkId/children")
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }

    private fun error() = DomusEngine.sendMessage(
        MessageType.NODE_INFO_TIMEOUT,
        networkId
    )
}