package it.achdjian.paolo.temperaturemonitor.zigbee

import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.DomusEngine
import java.util.*

/**
 * Created by Paolo Achdjian on 7/10/17.
 */
class ZDevices(val domusEngine: DomusEngine) {
    companion object {
        private val TAG = ZDevices::class.java.name
    }

    private val devices = TreeMap<Int, ZDevice>()

    fun addDevice(shortAddress:String, extendedAddress:String){
        try{
            val nwkAddress = Integer.parseInt(shortAddress, 16)
            if (!devices.containsKey(nwkAddress)){
                devices.put(nwkAddress,ZDevice(nwkAddress, extendedAddress,0))
            }
        } catch(e:Exception){

        }
    }
}