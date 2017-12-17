package it.achdjian.paolo.cs5463.zigbee

import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.rest.JsonDevice
import it.achdjian.paolo.cs5463.zigbee.ZEndpoint
import it.achdjian.paolo.cs5463.zigbee.ZDevice
import it.achdjian.paolo.cs5463.zigbee.nullZDevice
import java.util.*
import javax.inject.Inject

/**
 * Created by Paolo Achdjian on 7/10/17.
 */
class ZDevices @Inject constructor() {
    lateinit var domusEngine: DomusEngine

    companion object {
        private val TAG = ZDevices::class.java.name
    }

    private val devices = TreeMap<Int, ZDevice>()

    fun getDevices():Collection<ZDevice>{
        return devices.values
    }

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

    fun get(networkAddr: Int): ZDevice {
        val zDevice = devices[networkAddr]
        if (zDevice == null)
            return nullZDevice
        else
            return zDevice;
    }

    fun get(extendAddr: String): ZDevice {
        devices.values.forEach({if (it.extendedAddr==extendAddr)return it})
        return nullZDevice
    }

    fun addEndpoint(endpoint: ZEndpoint) {
        if (devices.containsKey(endpoint.short_address)) {
            devices[endpoint.short_address]?.endpoints?.put(endpoint.endpoint_id, endpoint)
        }
    }

    fun existDevice(network: Int): Boolean {
        devices.forEach({if (it.value.shortAddress == network) return true})
        return false
    }


}