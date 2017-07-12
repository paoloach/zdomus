package it.achdjian.paolo.temperaturemonitor.zigbee

import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.JsonDevice
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.handler
import java.util.*

/**
 * Created by Paolo Achdjian on 7/10/17.
 */
class ZDevices() {
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
                forEach { handler.sendMessage(handler.obtainMessage(MessageType.GET_DEVICE, it)) }
    }

    fun addDevice(newDevice: JsonDevice) {
        val device = ZDevice(newDevice)
        devices[device.shortAddress] = device
    }

    fun addEndpoint(endpoint: ZEndpoint) {
        if (devices.containsKey(endpoint.shortAddress)){
            devices[endpoint.shortAddress]?.endpoints?.put(endpoint.id,endpoint)
        }
    }


}