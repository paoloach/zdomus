package it.achdjian.paolo.ztopology.zigbee

import android.util.Log
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.LogicalType
import it.achdjian.paolo.ztopology.LqiInfoCallback
import it.achdjian.paolo.ztopology.rest.LQI
import it.achdjian.paolo.ztopology.zigbee.Topology.Companion.root

/**
 * Created by Paolo Achdjian on 1/18/18.
 */

interface TopologyUpdate {
    fun update()
}

object TopologyManager : LqiInfoCallback {
    const val TAG = "topologyManager"
    override fun lqiInfo(response: LQI) {
        Log.i(TAG, "new LQI info: ${response.nwkAddrOwner}")
        val node = Topology.root.findNode(response.nwkAddrOwner)
        if (node != null) {
            Log.i(TAG, "node found")
            if (node.children.isEmpty()) {
                IntRange(0, response.totTable-1).forEach { node.children.add(Topology()) }
            }
            response.tables
                .forEach {
                    if (it.logicalType != LogicalType.ZigbeeEnddevice && it.depth > node.depth) {
                        DomusEngine.requestLQI(it.nwkAddr, 0)
                    }
                    val child = Topology(
                        it.panAddr,
                        it.extAddr,
                        it.nwkAddr,
                        it.logicalType,
                        it.relationship,
                        it.depth,
                        it.lqi
                    )
                    node.children[it.index] = child
                }
            val missingTable = IntRange( 0, response.totTable-1)
                .firstOrNull { node.children[it].logicalType == LogicalType.Invalid }
            if (missingTable != null) {
                DomusEngine.requestLQI(node.nwkAddress, missingTable)
            }

            updateViews()
        }
    }

    override fun lqiInfoTimeout(networkId: Int) {
        DomusEngine.requestNode(networkId)
    }

    private val views = HashSet<TopologyUpdate>()

    private fun updateViews() {
        views.forEach { it.update() }
    }

    fun addView(view: TopologyUpdate) = views.add(view)
    fun removeView(view: TopologyUpdate) = views.remove(view)

    fun deepth(): Int {
        return root.maxDepth()
    }

    fun log() {
        return root.log(0)
    }

    fun start() {
        DomusEngine.requestLQI(0, 0)
    }

}