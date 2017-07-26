package it.achdjian.paolo.temperaturemonitor.domusEngine

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.Constants
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.*
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class DomusEngine(val whoAreYou: WhoAreYou, val getDevices: GetDevices, val zDevices: ZDevices, val domusEngineRest: DomusEngineRest) : HandlerThread("DomusEngtine"), Handler.Callback {
    val handler: Handler
    val listeners: MutableList<NewTemperatureDeviceListener> = ArrayList()

    companion object {
        val TAG="ZIGBEE COM"
    }

    init {
        zDevices.domusEngine = this;
        start()
        handler = Handler(looper, this)
        handler.post(whoAreYou)
    }

    fun getDevices() = handler.post(getDevices)

    fun getDevice(device: Int) = handler.sendMessage(handler.obtainMessage(MessageType.GET_DEVICE, device, 0))


    fun addListener(listener: NewTemperatureDeviceListener)= listeners.add(listener)

    override fun handleMessage(message: Message?): Boolean {
        if (message != null) {
            when (message.what) {
                MessageType.WHO_ARE_YOU ->{
                    handler.post(whoAreYou)
                    Log.i(TAG, "Who are You")
                }
                MessageType.GET_DEVICES ->{
                    handler.post(getDevices)
                    Log.i(TAG, "Get Devices")
                }
                MessageType.GET_DEVICE -> {
                    handler.post(GetDevice(message.arg1, domusEngineRest, this))
                    Log.i(TAG, "Get Device")
                }
                MessageType.NEW_DEVICE -> {
                    Log.i(TAG, "NEW Device")
                    val device = message.obj as JsonDevice
                    zDevices.addDevice(device)
                    device.endpoints.
                            forEach {
                                handler.post(GetEndpoint(device.short_address, Integer.parseInt(it.value, 16), domusEngineRest, this)) }
                }
                MessageType.NEW_ENDPOINT -> {
                    Log.i(TAG, "NEW endpoint_id")
                    val endpoint = message.obj as ZEndpoint
                    zDevices.addEndpoint(endpoint)
                    if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR) {
                        listeners.forEach({it.newTemperatureDevice(endpoint.short_address, endpoint.endpoint_id.toInt(16))})
                    }
                }
            }
        }
        return true
    }

}