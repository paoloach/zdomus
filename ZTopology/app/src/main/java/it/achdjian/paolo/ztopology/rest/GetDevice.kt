package it.achdjian.paolo.ztopology.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable.Companion.MAPPER
import it.achdjian.paolo.ztopology.domusEngine.rest.JsonDevice
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetDevice(val nwkAddress: Int) : ZigbeeRunnable() {
    override fun run() {
        val body = DomusEngineRest.get("/devices/" + nwkAddress.toString(16))
        if (body.isNotBlank()) {
            try {
                Log.i("REST", body)
                val zDevice = MAPPER.readValue(body, JsonDevice::class.java)
                DomusEngine.handler.sendMessage(DomusEngine.handler.obtainMessage(MessageType.NEW_DEVICE, zDevice))
                Log.i("REST", zDevice.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/" + nwkAddress)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }

}