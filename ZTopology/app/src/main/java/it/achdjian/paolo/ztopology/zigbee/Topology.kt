package it.achdjian.paolo.ztopology.zigbee

import android.util.Log
import it.achdjian.paolo.ztopology.LogicalType
import it.achdjian.paolo.ztopology.rest.Relationship

/**
 * Created by Paolo Achdjian on 1/18/18.
 */
enum class DeviceConnectionStatus {
    WAITING,
    CONNECTED,
    DISCONNECTED
}

class Topology(val panAddress: String,
               val extendedAddr: String,
               val nwkAddress: Int,
               val logicalType: LogicalType,
               val relationship: Relationship,
               val depth: Int,
               val lqi: Int) {
    constructor(nwkAddress: Int):this("","",nwkAddress,LogicalType.ZigbeeCordinator, Relationship.NoRelation, 0, 200)
    constructor():this("","",-1,LogicalType.Invalid, Relationship.NoRelation, 0, 200)


    var children:MutableList<Topology> = ArrayList<Topology>()
    var connectionStatus = DeviceConnectionStatus.CONNECTED
    var capabilities: Int = 0


    companion object {
        var root = Topology(0)
        val spaces = "                "
    }

    fun findNode(networkdId: Int): Topology ?{
        if (networkdId == nwkAddress) {
            return this
        }
        return children.map{it.findNode(networkdId)}.firstOrNull { it != null }
    }

    fun maxDepth(): Int {
        var max=depth
        children.forEach({
            val depth = it.maxDepth()
            if (depth > max)
                max = depth
        })
        return max+1
    }

    fun log(depth: Int){
        Log.i("TopologyView", spaces.substring(0,4*depth) + nwkAddress.toString(16) + ", status " + connectionStatus)
        children.forEach { it.log(depth+1) }
    }



}
