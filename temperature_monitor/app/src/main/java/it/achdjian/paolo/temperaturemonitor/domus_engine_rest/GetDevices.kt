package it.achdjian.paolo.temperaturemonitor.domus_engine_rest

import android.os.Handler
import com.fasterxml.jackson.core.type.TypeReference
import com.fasterxml.jackson.databind.ObjectMapper
import java.io.IOException

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class GetDevices(val domusEngineRest: DomusEngineRest) : Runnable {
    override fun run() {
        val body = domusEngineRest.get("/devices")
        if (body != null) {
            if (!body!!.isEmpty()) {
                val mapper = ObjectMapper()
                try {
                    val devices = mapper.readValue<Map<String, String>>(body, object : TypeReference<Map<String, String>>() {

                    })
//                    for (entry in devices.entries) {
//                        zDevices.addDevice(entry.key, entry.value)
//                    }
                } catch (e: IOException) {
                    e.printStackTrace()
                }

            }
            Handler().postDelayed(this, 2000)
        }
    }
}