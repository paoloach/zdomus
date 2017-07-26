package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.os.Handler
import com.fasterxml.jackson.core.type.TypeReference
import com.fasterxml.jackson.databind.ObjectMapper
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import java.io.IOException
import java.util.*

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class GetDevices(val domusEngineRest: DomusEngineRest, val zDevices: ZDevices) : ZigbeeRunnable() {
    override fun run() {
        val handler = Handler()
        val body = domusEngineRest.get("/devices")
        if (body.isNotBlank()) {
            val mapper = ObjectMapper()
            try {
                val devices = mapper.readValue<Map<String, String>>(body, object : TypeReference<Map<String, String>>() {

                })
                val nwkAddresses = devices.mapKeys { Integer.parseInt(it.key, 16) }
                zDevices.addDevices(nwkAddresses)
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        handler.removeMessages(MessageType.WHO_ARE_YOU)
        val message = handler.obtainMessage(MessageType.WHO_ARE_YOU)
        handler.sendMessageDelayed(message, 600000)
    }
}