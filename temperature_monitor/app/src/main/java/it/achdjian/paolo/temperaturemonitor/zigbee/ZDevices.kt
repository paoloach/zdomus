package it.achdjian.paolo.temperaturemonitor.zigbee

import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.JsonDevice
import java.util.*

/**
 * Created by Paolo Achdjian on 7/10/17.
 */
class ZDevices() {
    lateinit var domusEngine: DomusEngine

    companion object {
        private val TAG = ZDevices::class.java.name
    }

    private val devices = TreeMap<Int, ZDevice>()

    fun addDevices(newDevices: Map<Int, String>) {
        val iter = devices.iterator()
        while (iter.hasNext()) {
            val networkAddress = iter.next().key
            if (!newDevices.containsKey(networkAddress)) {
                iter.remove()
            }
        }
        newDevices.keys.
                filter { !devices.contains(it) }.
                forEach { domusEngine.getDevice(it) }
    }

    fun addDevice(newDevice: JsonDevice) {
        val device = ZDevice(newDevice)
        devices[device.shortAddress] = device
    }

    fun addEndpoint(endpoint: ZEndpoint) {
        if (devices.containsKey(endpoint.short_address)){
            devices[endpoint.short_address]?.endpoints?.put(endpoint.endpoint_id.toInt(16),endpoint)
        }
    }


}