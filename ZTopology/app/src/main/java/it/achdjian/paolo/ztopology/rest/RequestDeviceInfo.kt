package it.achdjian.paolo.ztopology.rest

import android.util.Log
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import java.io.IOException

/**
 * Created by Paolo Achdjian on 1/29/18.
 */
class RequestDeviceInfo(val networkId: Int) : ZigbeeRunnable()  {
    override fun run() {
        Log.i(TAG,"Request device info for " + networkId)
        val path = "/devices/" + networkId.toString(16) + "/info"

        val body = DomusEngineRest.get(path,action= this::error)
        if (body.isNotBlank()) {
            try {
                Log.i(TAG, body)
                val deviceInfo = MAPPER.readValue(body, JSonDeviceInfo::class.java)
                DomusEngine.handler.sendMessage(DomusEngine.handler.obtainMessage(MessageType.NEW_DEVICE_INFO, DeviceInfo(deviceInfo)))
                Log.i(TAG, deviceInfo.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/$networkId/info")
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }
    fun error() = DomusEngine.sendMessage(MessageType.DEVICE_INFO_TIMEOUT, networkId)
}