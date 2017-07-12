package it.achdjian.paolo.temperaturemonitor.domusEngine

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.*
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class DomusEngine(val whoAreYou: WhoAreYou, val getDevices: GetDevices, val zDevices: ZDevices, val domusEngineRest: DomusEngineRest) : HandlerThread("DomusEngtine"), Handler.Callback {
    val handler: Handler

    init {
        start()
        handler = Handler(looper, this)
        handler.post(whoAreYou)
    }

    fun getDevices() = handler.post(getDevices)

    override fun handleMessage(message: Message?): Boolean {
        if (message != null) {
            when (message.what) {
                MessageType.WHO_ARE_YOU -> handler.post(whoAreYou)
                MessageType.GET_DEVICES -> handler.post(getDevices)
                MessageType.GET_DEVICE -> handler.post(GetDevice(message.arg1, domusEngineRest))
                MessageType.NEW_DEVICE -> {
                    val device = message.obj as JsonDevice
                    zDevices.addDevice(device)
                    device.endpoints.
                            forEach {
                                handler.post(GetEndpoint(device.short_address, Integer.parseInt(it.value, 16), domusEngineRest)) }
                }
                MessageType.NEW_ENDPOINT -> {
                    val endpoint = message.obj as ZEndpoint
                    zDevices.addEndpoint(endpoint)
                }
            }
        }
        return true
    }

}