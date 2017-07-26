package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.os.Handler
import android.util.Log
import com.fasterxml.jackson.databind.ObjectMapper
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.ZigbeeRunnable.Companion.MAPPER
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetDevice(val nwkAddress: Int, val domusEngineRest: DomusEngineRest, val domusEngine: DomusEngine) : ZigbeeRunnable() {
    override fun run() {
        val body = domusEngineRest.get("/devices/" + nwkAddress.toString(16))
        if (body.isNotBlank()) {
            try {
                val zDevice = MAPPER.readValue(body, JsonDevice::class.java)
                domusEngine.handler.sendMessage(domusEngine.handler.obtainMessage(MessageType.NEW_DEVICE, zDevice))
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for /devices/" + nwkAddress)
                Log.e(TAG, "Response: " + body)
                e.printStackTrace()
            }
        }
    }

}