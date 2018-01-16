package it.achdjian.paolo.ztopology.zigbee

import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.domusEngine.rest.JsonDevice
import java.util.*


/**
 * Created by Paolo Achdjian on 7/10/17.
 */
object ZDevices {
    private val devices = TreeMap<Int, ZDevice>()

    fun addDevices(newDevices: Map<Int, String>) {
        val iter = devices.iterator()
        while (iter.hasNext()) {
            val networkAddress = iter.next().key
            if (!newDevices.containsKey(networkAddress)) {
                iter.remove()
            }
        }
        newDevices
                .keys
                .filter { !devices.contains(it) }
                .forEach { DomusEngine.getDevice(it)}
    }

    fun addDevice(newDevice: JsonDevice) {
        val device = ZDevice(newDevice)
        devices[device.shortAddress] = device
    }

    fun get(networkAddr: Int): ZDevice {
        val zDevice = devices[networkAddr]
        if (zDevice == null)
            return nullZDevice
        else
            return zDevice;
    }

    fun get(extendAddr: String): ZDevice {
        devices.values.forEach({ if (it.extendedAddr == extendAddr) return it })
        return nullZDevice
    }

    fun addEndpoint(endpoint: ZEndpoint) {
        if (devices.containsKey(endpoint.short_address)) {
            devices[endpoint.short_address]?.endpoints?.put(endpoint.endpoint_id, endpoint)
        }
    }

    fun existDevice(network: Int): Boolean {
        devices.forEach({ if (it.value.shortAddress == network) return true })
        return false
    }


}