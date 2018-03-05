package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.GridLayout
import android.widget.TextView
import it.achdjian.paolo.ztopology.AttributesCallback
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.domusEngine.rest.Attributes
import it.achdjian.paolo.ztopology.zigbee.Cluster
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/28/18.
 */
abstract class ClusterFragment : Fragment() , AttributesCallback {
    lateinit var endpoint: ZEndpoint
    private val mapView = HashMap<Int, TextView>()

    abstract fun layoutResource(): Int
    abstract fun clusterId(): Cluster

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if (arguments != null) {
            endpoint = arguments.getSerializable(NodeActivity.ENDPOINT) as ZEndpoint
        }
        DomusEngine.addCallback(this)
    }

    override fun onDestroy() {
        super.onDestroy()
        DomusEngine.removeCallback(this)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?
    ): View? {
        val rootView = inflater.inflate(layoutResource(), container, false)

        if (rootView is GridLayout) {
            IntRange(0, rootView.childCount-1).forEach {
                val child = rootView.getChildAt(it)
                if (child.tag != null && child.tag is String) {
                    mapView[(child.tag as String).toInt()] = child as TextView
                }
            }
        }
        DomusEngine.getAttributes(
            endpoint.networkAddress, endpoint.endpointId, clusterId(), mapView.keys.toList()
        )
        return rootView
    }

    override fun newAttributes(response: Attributes){
        if (response.networkId == endpoint.networkAddress &&
                response.endpointId == endpoint.endpointId &&
                response.clusterId == clusterId()){
            activity.runOnUiThread({
                response.values
                    .filter { it.isAvailable }
                    .map { mapView[it.id]?.text = it.value }
                response.values
                    .filter { it.isAvailable == false && it.isSupported }
                    .map { mapView[it.id]?.text = "Not available" }
                response.values
                    .filter { it.isSupported == false }
                    .map { mapView[it.id]?.text = "Not supported" }
            })

        }
    }

}