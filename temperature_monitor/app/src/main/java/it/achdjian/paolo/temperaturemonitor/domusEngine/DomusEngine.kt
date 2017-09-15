package it.achdjian.paolo.temperaturemonitor.domusEngine

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.Constants
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.*
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.zigbee.PowerNode
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import it.achdjian.paolo.temperaturemonitor.zigbee.ZEndpoint
import java.util.concurrent.LinkedBlockingQueue
import java.util.concurrent.ThreadPoolExecutor
import java.util.concurrent.TimeUnit

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
    private val powerListener: MutableSet<PowerListener> = HashSet()
    private val mDecodeWorkQueue =  LinkedBlockingQueue<Runnable>();
    private val threadPool = ThreadPoolExecutor(3, Int.MAX_VALUE, 60, TimeUnit.SECONDS, mDecodeWorkQueue)


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

    fun getDevice(device: Int) = handler.post(GetDevice(device, domusEngineRest, this))

    fun getAttribute(networkId: Int, endpointId: Int, clusterId: Int, attributeId: Int) =
            threadPool.execute(RequestAttributes(AttributeCoord(networkId, endpointId, clusterId, attributeId), domusEngineRest, this))

    fun addListener(listener: NewTemperatureDeviceListener) = listeners.add(listener)
    fun addListener(listener: PowerListener) = powerListener.add(listener)
    fun removeListener(listener: PowerListener) = powerListener.remove(listener)

    fun addAttributeListener(listener: AttributesListener) = attributeListener.add(listener)

    fun requestIdentify(shortAddress: Int, endpointId: Int)  =
        threadPool.execute(RequestIdentify(shortAddress, endpointId,domusEngineRest));

    fun requestPower(shortAddress: Int) =
        threadPool.execute(RequestPowerNode(shortAddress, domusEngineRest, this))

    override fun handleMessage(message: Message?): Boolean {
        if (message != null) {
            when (message.what) {
                MessageType.WHO_ARE_YOU -> {
                    handler.post(whoAreYou)
                    Log.i(TAG, "Who are You")
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
                MessageType.NEW_ATTRIBUTES -> {
                    Log.i(TAG, "new attributes")
                    val attributes = message.obj as Attributes
                    attributeListener.forEach({ it.newAttributes(attributes) })
                }
                MessageType.NEW_POWER -> {
                    Log.i(TAG, "new power node response")
                    val powerNode = message.obj as PowerNode
                    powerListener.forEach({ it.newPower(powerNode) })
                }
            }
        }
        return true
    }


}
