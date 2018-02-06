package it.achdjian.paolo.ztopology.rest

import android.util.Log
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import java.io.IOException

/**
 * Created by Paolo Achdjian on 1/16/18.
 */
class RequestChildren(val networkId: Int) : ZigbeeRunnable()  {
    override fun run() {
        Log.i(TAG,"Request node information for " + networkId)
        val path = "/devices/" + networkId.toString(16) + "/children"

        val body = DomusEngineRest.get(path,action= this::error)
        if (body.isNotBlank()) {
            try {
                Log.i(TAG, body)
                val children = MAPPER.readValue(body, JsonChildren::class.java)
                DomusEngine.handler.sendMessage(DomusEngine.handler.obtainMessage(MessageType.NEW_CHILDREN, Children(children)))
                Log.i("REST", children.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$networkId/children")
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }

    fun error() = DomusEngine.sendMessage(MessageType.NODE_INFO_TIMEOUT, networkId )
}