package it.achdjian.paolo.cs5463.domusEngine

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.util.Log
import it.achdjian.paolo.cs5463.Constants
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine.handler
import it.achdjian.paolo.cs5463.domusEngine.rest.*
import it.achdjian.paolo.cs5463.zigbee.PowerNode
import it.achdjian.paolo.cs5463.zigbee.ZDevices
import it.achdjian.paolo.cs5463.zigbee.ZEndpoint
import java.util.concurrent.LinkedBlockingQueue
import java.util.concurrent.ThreadPoolExecutor
import java.util.concurrent.TimeUnit

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
object DomusEngine : HandlerThread("DomusEngtine"), Handler.Callback {
    val handler: Handler
    val whoAreYou = WhoAreYou()
    val getDevices = GetDevices()
    private val listeners: MutableList<NewSmartPlugDeviceListener> = ArrayList()
    private val attributeListener: MutableList<AttributesListener> = ArrayList()
    private val powerListener: MutableSet<PowerListener> = HashSet()
    private val mDecodeWorkQueue =  LinkedBlockingQueue<Runnable>();
    private val threadPool = ThreadPoolExecutor(3, Int.MAX_VALUE, 60, TimeUnit.SECONDS, mDecodeWorkQueue)

    val TAG = "ZIGBEE COM"

    init {
        start()
        handler = Handler(looper, this)

    }

    fun startEngine() {
        handler.post(whoAreYou)
    }

    fun getDevices() = handler.post(getDevices)

    fun getDevice(device: Int) = handler.post(GetDevice(device))

    fun getAttribute(networkId: Int, endpointId: Int, clusterId: Int, attributeId: Int) =
            threadPool.execute(RequestAttributes(AttributeCoord(networkId, endpointId, clusterId, attributeId)))


    fun addListener(listener: NewSmartPlugDeviceListener) = listeners.add(listener)
    fun addListener(listener: PowerListener) = powerListener.add(listener)
    fun removeListener(listener: PowerListener) = powerListener.remove(listener)

    fun requestWhoAreYou() {

    }

    fun addAttributeListener(listener: AttributesListener) = attributeListener.add(listener)

    fun requestIdentify(shortAddress: Int, endpointId: Int)  =
        threadPool.execute(RequestIdentify(shortAddress, endpointId));

    fun requestPower(shortAddress: Int) =
        threadPool.execute(RequestPowerNode(shortAddress))

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
                    ZDevices.addDevice(device)
                    device.endpoints.
                            forEach {
                                val endpoint = it.value.toInt(16)
                                handler.post(GetEndpoint(device.short_address, endpoint))
                            }

                }
                MessageType.NEW_ENDPOINT -> {
                    Log.i(TAG, "NEW endpoint_id")
                    val endpoint = message.obj as ZEndpoint
                    ZDevices.addEndpoint(endpoint)
                    if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_SMART_PLUG) {
                        listeners.forEach({ it.newSmartPlugDevice(endpoint.short_address, endpoint.endpoint_id) })
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
