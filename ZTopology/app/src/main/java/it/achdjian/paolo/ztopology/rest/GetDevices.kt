package it.achdjian.paolo.ztopology.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import com.fasterxml.jackson.databind.ObjectMapper
import com.google.common.base.Joiner
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.zigbee.ZDevices
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class GetDevices : ZigbeeRunnable() {
    override fun run() {
        val body = DomusEngineRest.get("/devices")
        if (body.isNotBlank()) {
            val mapper = ObjectMapper()
            try {
                val devices = mapper.readValue<Map<String, String>>(body, object : TypeReference<Map<String, String>>() {

                })
                val nwkAddresses = devices.mapKeys { Integer.parseInt(it.key, 16) }
                Log.i(TAG, "Arrived device: " + Joiner.on(",").join(devices.keys))
                ZDevices.addDevices(nwkAddresses)
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        DomusEngine.handler.removeMessages(MessageType.WHO_ARE_YOU)
        val message = DomusEngine.handler.obtainMessage(MessageType.WHO_ARE_YOU)
        DomusEngine.handler.sendMessageDelayed(message, 600000)
    }
}