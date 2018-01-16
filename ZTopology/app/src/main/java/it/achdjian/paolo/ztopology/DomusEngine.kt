package it.achdjian.paolo.ztopology

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.rest.*
import it.achdjian.paolo.ztopology.zigbee.ZDevices
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint
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
    private val mDecodeWorkQueue = LinkedBlockingQueue<Runnable>();
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


    fun postCmd(networkId: Int, endpointId: Int, clusterId: Int, cmdId: Int) =
            threadPool.execute(ExecuteCommand(networkId, endpointId, clusterId, cmdId))


    fun requestWhoAreYou() {

    }

    fun requestChildren(shortAddress: Int) {
        threadPool.execute(RequestIdentify(shortAddress, endpointId));
    }

    fun requestIdentify(shortAddress: Int, endpointId: Int) =
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
                }
            }
        }
        return true
    }

}
