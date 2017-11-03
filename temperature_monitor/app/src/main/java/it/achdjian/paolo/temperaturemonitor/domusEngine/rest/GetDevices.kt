package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import com.fasterxml.jackson.databind.ObjectMapper
import com.google.common.base.Joiner
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class GetDevices(val domusEngine: DomusEngine, val domusEngineRest: DomusEngineRest, val zDevices: ZDevices) : ZigbeeRunnable() {
    override fun run() {
        val body = domusEngineRest.get("/devices")
        if (body.isNotBlank()) {
            val mapper = ObjectMapper()
            try {
                val devices = mapper.readValue<Map<String, String>>(body, object : TypeReference<Map<String, String>>() {

                })
                val nwkAddresses = devices.mapKeys { Integer.parseInt(it.key, 16) }
                Log.i(TAG, "Arrived device: " + Joiner.on(",").join(devices.keys))
                zDevices.addDevices(nwkAddresses)
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        domusEngine.handler.removeMessages(MessageType.WHO_ARE_YOU)
        val message = domusEngine.handler.obtainMessage(MessageType.WHO_ARE_YOU)
        domusEngine.handler.sendMessageDelayed(message, 600000)
    }
}