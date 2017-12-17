package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.MessageType
import it.achdjian.paolo.cs5463.domusEngine.rest.JsonDevice
import it.achdjian.paolo.cs5463.domusEngine.rest.ZigbeeRunnable
import it.achdjian.paolo.cs5463.domusEngine.rest.ZigbeeRunnable.Companion.MAPPER
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetDevice(val nwkAddress: Int, val domusEngineRest: DomusEngineRest, val domusEngine: DomusEngine) : ZigbeeRunnable() {
    override fun run() {
        val body = domusEngineRest.get("/devices/" + nwkAddress.toString(16))
        if (body.isNotBlank()) {
            try {
                Log.i("REST", body)
                val zDevice = MAPPER.readValue(body, JsonDevice::class.java)
                domusEngine.handler.sendMessage(domusEngine.handler.obtainMessage(MessageType.NEW_DEVICE, zDevice))
                Log.i("REST", zDevice.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/" + nwkAddress)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }

}