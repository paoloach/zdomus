package it.achdjian.paolo.temperaturemonitor.domus_engine_rest

import android.os.Handler
import com.fasterxml.jackson.core.type.TypeReference
import com.fasterxml.jackson.databind.ObjectMapper
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class GetDevices(val domusEngineRest: DomusEngineRest, val zDevices: ZDevices) : Runnable {
    override fun run() {
        val body = domusEngineRest.get("/devices")
        if (body != null) {
            if (!body!!.isEmpty()) {
                val mapper = ObjectMapper()
                try {
                    val devices = mapper.readValue<Map<String, String>>(body, object : TypeReference<Map<String, String>>() {

                    })
                    for ((key, value) in devices) {
                        zDevices.addDevice(key, value)
                    }
                } catch (e: IOException) {
                    e.printStackTrace()
                }

            }
        }
    }
}