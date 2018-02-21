package it.achdjian.paolo.ztopology

import android.os.Handler
import android.os.HandlerThread
import android.os.Message
import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.rest.*
import it.achdjian.paolo.ztopology.rest.*
import it.achdjian.paolo.ztopology.zigbee.ZDevices
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint
import java.util.*
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
    val childrenCallback = HashSet<ChildrenCallback>()
    val deviceCallback = HashSet<DeviceCallback>()
    val deviceInfoCallback = HashSet<DeviceInfoCallback>()
    val nodeInfoCallback = HashSet<NodeInfoCallback>()
    val lqiInfoCallback = HashSet<LqiInfoCallback>()

    private val mDecodeWorkQueue = LinkedBlockingQueue<Runnable>();
    private val threadPool =
        ThreadPoolExecutor(3, Int.MAX_VALUE, 60, TimeUnit.SECONDS, mDecodeWorkQueue)

    val TAG = "ZIGBEE COM"

    init {
        start()
        handler = Handler(looper, this)
    }

    fun startEngine() {
        handler.post(whoAreYou)
    }

    fun requestWhoAreYou() = handler.post(whoAreYou)

    fun getDevices() = handler.post(getDevices)

    fun getDevice(device: Int) = handler.post(GetDevice(device))


    fun postCmd(networkId: Int, endpointId: Int, clusterId: Int, cmdId: Int) =
        threadPool.execute(ExecuteCommand(networkId, endpointId, clusterId, cmdId))


    fun requestChildren(shortAddress: Int) =
        threadPool.execute(RequestChildren(shortAddress))

    fun requestNode(shortAddress: Int) =
        threadPool.execute(RequestNodeInfo(shortAddress))

    fun requestDeviceInfo(shortAddress: Int) =
        threadPool.execute(RequestDeviceInfo(shortAddress))

    fun requestIdentify(shortAddress: Int, endpointId: Int) =
        threadPool.execute(RequestIdentify(shortAddress, endpointId))

    fun requestPower(shortAddress: Int) = threadPool.execute(RequestPowerNode(shortAddress))

    fun requestLQI(shortAddress: Int, index: Int) =
        threadPool.execute(RequestLQI(shortAddress, index))

    fun addCallback(callback: ChildrenCallback) = childrenCallback.add(callback)
    fun addCallback(callback: DeviceCallback) = deviceCallback.add(callback)
    fun addCallback(callback: NodeInfoCallback) = nodeInfoCallback.add(callback)
    fun addCallback(callback: LqiInfoCallback) = lqiInfoCallback.add(callback)
    fun addCallback(callback: DeviceInfoCallback) = deviceInfoCallback.add(callback)
    fun removeCallback(callback: ChildrenCallback) = childrenCallback.remove(callback)
    fun removeCallback(callback: NodeInfoCallback) = nodeInfoCallback.remove(callback)
    fun removeCallback(callback: LqiInfoCallback) = lqiInfoCallback.remove(callback)

    fun sendMessage(messageType: Int, obj: Any) {
        handler.sendMessage(handler.obtainMessage(messageType, obj))
    }

    override fun handleMessage(message: Message?): Boolean {
        if (message != null) {
            when (message.what) {
                MessageType.WHO_ARE_YOU -> {
                    handler.post(whoAreYou)
                    Log.i(TAG, "Who are You")
                }
                MessageType.NEW_DEVICE -> {
                    val device = message.obj as JsonDevice
                    ZDevices.addDevice(device)
                    deviceCallback.forEach { it.newDevice(device) }
                }
                MessageType.DEVICE_TIMEOUT -> {
                    val networkId = message.obj as Int
                    Log.i(TAG, "Timeout requesting device for {networkId}")
                    deviceCallback.forEach { it.deviceTimeout(networkId) }
                }
                MessageType.NEW_ENDPOINT -> {
                    Log.i(TAG, "NEW endpoint_id")
                    val endpoint = message.obj as ZEndpoint
                    ZDevices.addEndpoint(endpoint)
                }
                MessageType.NEW_CHILDREN -> {
                    val response = message.obj as Children
                    childrenCallback.forEach { it.newChildrenResult(response) }
                }
                MessageType.CHILDREN_TIMEOUT -> {
                    val networkId = message.obj as Int
                    Log.i(TAG, "Timeout requesting children for {networkId}")
                    childrenCallback.forEach { it.childrenTimeout(networkId) }
                }
                MessageType.NEW_DEVICE_INFO -> {
                    val response = message.obj as DeviceInfo
                    deviceInfoCallback.forEach { it.newDeviceInfo(response) }
                }
                MessageType.DEVICE_INFO_TIMEOUT -> {
                    val networkId = message.obj as Int
                    Log.i(TAG, "Timeout requesting device info for {networkId}")
                    deviceInfoCallback.forEach { it.deviceInfoTimeout(networkId) }
                }
                MessageType.NEW_NODE_INFO -> {
                    val response = message.obj as NodeInfo
                    nodeInfoCallback.forEach { it.newNodeInfo(response) }
                }
                MessageType.NODE_INFO_TIMEOUT -> {
                    val networkId = message.obj as Int
                    Log.i(TAG, "Timeout requesting node info for {networkId}")
                    nodeInfoCallback.forEach { it.nodeInfoTimeout(networkId) }
                }

                MessageType.LQI_INFO -> {
                    val response = message.obj as LQI
                    lqiInfoCallback.forEach { it.lqiInfo(response) }
                }

                MessageType.LQI_INFO_TIMEOUT -> {
                    val response = message.obj as Int
                    Log.i(TAG, "Timeout requesting LQI info for {networkId}")
                    lqiInfoCallback.forEach { it.lqiInfoTimeout(response) }
                }
            }
        }
        return true
    }

}

interface ChildrenCallback {
    fun newChildrenResult(response: Children);
    fun childrenTimeout(networkId: Int)
}

interface DeviceCallback {
    fun newDevice(response: JsonDevice);
    fun deviceTimeout(networkId: Int)
}

interface DeviceInfoCallback {
    fun newDeviceInfo(response: DeviceInfo);
    fun deviceInfoTimeout(networkId: Int)
}


interface NodeInfoCallback {
    fun newNodeInfo(response: NodeInfo);
    fun nodeInfoTimeout(networkId: Int)
}

interface LqiInfoCallback {
    fun lqiInfo(response: LQI);
    fun lqiInfoTimeout(networkId: Int)
}