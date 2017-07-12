package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.os.Handler
import android.util.Log
import com.fasterxml.jackson.databind.ObjectMapper
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.ZigbeeRunnable.Companion.MAPPER
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/11/17.
 */
class GetDevice(val nwkAddress:Int,val domusEngineRest: DomusEngineRest) : ZigbeeRunnable() {
    override fun run() {
        val body = domusEngineRest.get("/devices/" + nwkAddress)
        if (body != null) {
            if (!body.isEmpty()) {
                try {
                    val zDevice = MAPPER.readValue(body, JsonDevice::class.java)
                    val handler = Handler()
                    handler.sendMessage(handler.obtainMessage(MessageType.NEW_DEVICE,zDevice))
                } catch (e: IOException) {
                    Log.e(TAG, "Error parsing response for /devices/"+nwkAddress)
                    Log.e(TAG, "Response: " + body)
                    e.printStackTrace()
                }
            }
        }
    }

}