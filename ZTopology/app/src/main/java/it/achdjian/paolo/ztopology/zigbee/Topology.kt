package it.achdjian.paolo.ztopology.zigbee

import android.util.Log
import it.achdjian.paolo.ztopology.LogicalType
import it.achdjian.paolo.ztopology.NodeInfo

/**
 * Created by Paolo Achdjian on 1/18/18.
 */
enum class DeviceConnectionStatus {
    WAITING,
    CONNECTED,
    DISCONNECTED
}

class Topology(val shortAddress: Int) {
    val children = ArrayList<Topology>()
    var extendedAddr: String = ""
    var connectionStatus = DeviceConnectionStatus.WAITING
    var capabilities: Int = 0
    var logicalType = LogicalType.Invalid

    companion object {
        var root = Topology(0)
        val spaces = "                "
    }

    fun findNode(networkdId: Int): Topology ?{
        if (networkdId == shortAddress) {
            return this
        }
        return children.map{it.findNode(networkdId)}.firstOrNull { it != null }
    }

    fun maxDepth(): Int {
        var max=0
        children.forEach({
            val depth = it.maxDepth()
            if (depth > max)
                max = depth
        })
        return max+1
    }

    fun log(depth: Int){
        Log.i("TopologyView", spaces.substring(0,4*depth) + shortAddress.toString(16) + ", status " + connectionStatus)
        children.forEach { it.log(depth+1) }
    }

    fun setInfo(response: NodeInfo) {
        logicalType = response.logicalType

    }


}
