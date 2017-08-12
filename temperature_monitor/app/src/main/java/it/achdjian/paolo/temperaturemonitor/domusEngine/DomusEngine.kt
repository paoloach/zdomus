package it.achdjian.paolo.temperaturemonitor.domusEngine

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.Constants
import it.achdjian.paolo.temperaturemonitor.TempSensorLocationDS
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.*
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpoint
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class DomusEngine(
        val zDevices: ZDevices,
        connectionStatus: ConnectionStatus,
        val rooms: Rooms,
        val domusEngineRest: DomusEngineRest) : HandlerThread("DomusEngtine"), Handler.Callback {
    val handler: Handler
    val whoAreYou = WhoAreYou(this, domusEngineRest, connectionStatus)
    val getDevices = GetDevices(this, domusEngineRest, zDevices)
    private val listeners: MutableList<NewTemperatureDeviceListener> = ArrayList()
    private val attributeListener: MutableList<AttributesListener> = ArrayList()


    companion object {
        val TAG = "ZIGBEE COM"

    }

    init {
        start()
        handler = Handler(looper, this)

    }

    fun startEngine() {
        handler.post(whoAreYou)
    }

    fun getDevices() = handler.post(getDevices)

    fun getDevice(device: Int) = handler.sendMessage(handler.obtainMessage(MessageType.GET_DEVICE, device, 0))

    fun getAttribute(networkId: Int, endpointId: Int, clusterId: Int, attributeId: Int) =
            handler.sendMessage(handler.obtainMessage(MessageType.GET_ATTRIBUTE, AttributeCoord(networkId, endpointId, clusterId, attributeId)))

    fun addListener(listener: NewTemperatureDeviceListener) = listeners.add(listener)

    fun addAttributeListener(listener: AttributesListener) = attributeListener.add(listener)

    override fun handleMessage(message: Message?): Boolean {
        if (message != null) {
            when (message.what) {
                MessageType.WHO_ARE_YOU -> {
                    handler.post(whoAreYou)
                    Log.i(TAG, "Who are You")
                }
                MessageType.GET_DEVICES -> {
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
                                val endpoint = it.value.toInt(16)
                                handler.post(GetEndpoint(device.short_address, endpoint, domusEngineRest, this))
                            }

                }
                MessageType.NEW_ENDPOINT -> {
                    Log.i(TAG, "NEW endpoint_id")
                    val endpoint = message.obj as ZEndpoint
                    zDevices.addEndpoint(endpoint)
                    if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR) {
                        listeners.forEach({ it.newTemperatureDevice(endpoint.short_address, endpoint.endpoint_id) })
                    }
                }
                MessageType.GET_ATTRIBUTE -> {
                    val coord = message.obj as AttributeCoord
                    Log.i(TAG, "Get attribute ${coord}")
                    handler.post(RequestAttributes(coord, domusEngineRest, this))
                }
                MessageType.NEW_ATTRIBUTES -> {
                    Log.i(TAG, "new attributes")
                    val attributes = message.obj as Attributes
                    attributeListener.forEach({ it.newAttributes(attributes) })
                }
            }
        }
        return true
    }
}
