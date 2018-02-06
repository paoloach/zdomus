package it.achdjian.paolo.ztopology.zigbee

import android.util.Log
import it.achdjian.paolo.ztopology.*
import it.achdjian.paolo.ztopology.domusEngine.rest.JsonDevice
import it.achdjian.paolo.ztopology.rest.Children
import it.achdjian.paolo.ztopology.view.TopologyView
import it.achdjian.paolo.ztopology.zigbee.Topology.Companion.root

/**
 * Created by Paolo Achdjian on 1/18/18.
 */

interface TopologyUpdate {
    fun update()
}

object TopologyManager : ChildrenCallback, DeviceCallback, NodeInfoCallback {
    override fun newNodeInfo(response: NodeInfo) {
        val node = Topology.root.findNode(response.nwkId)
        if (node != null){
            node.setInfo(response)
            updateViews()
        }
    }

    override fun nodeInfoTimeout(networkId: Int) {
        DomusEngine.requestNode(networkId)
    }

    private val views = HashSet<TopologyUpdate>()


    override fun deviceTimeout(networkId: Int) {
        DomusEngine.getDevice(networkId)
    }

    override fun newDevice(response: JsonDevice) {
        val node = Topology.root.findNode(response.short_address)
        if (node != null){
            node.capabilities = response.capability
            updateViews()
        }
    }

    override fun childrenTimeout(networkId: Int) {
        val node = Topology.root.findNode(networkId)
        if (node != null){
            node.connectionStatus = DeviceConnectionStatus.DISCONNECTED
        }
        updateViews()
    }

    override fun newChildrenResult(response: Children) {
        Log.i(TopologyView.TAG, "Response from " + response.nwkId)
        val node = Topology.root.findNode(response.nwkId)
        if (node != null) {
            if (node.children.size != response.children.size) {
                node.children.clear()
                response.children.forEach {
                    DomusEngine.requestChildren(it)
                    node.children.add(Topology(it))
                }
            }
            node.extendedAddr = response.extendAddr
            Log.i(TopologyView.TAG, "change " + node.shortAddress.toString(16) + " at connected")
            node.connectionStatus = DeviceConnectionStatus.CONNECTED
            DomusEngine.requestNode(node.shortAddress)
        }
        updateViews()
    }

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
        DomusEngine.requestChildren(0)
        DomusEngine.requestNode(0)
    }

}