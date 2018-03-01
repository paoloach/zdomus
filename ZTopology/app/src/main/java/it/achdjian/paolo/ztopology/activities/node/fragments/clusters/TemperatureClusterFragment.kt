package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.Constants
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

class TemperatureClusterFragment : ClusterFragment() {

    override fun layoutResource() : Int = R.layout.temperature_cluster
    override fun clusterId(): Int = Constants.TEMPERATURE_MEASUREMENT

    companion object {
        fun newInstance(endpoint: ZEndpoint): TemperatureClusterFragment {
            val fragment = TemperatureClusterFragment()
            val args = Bundle()
            args.putSerializable(NodeActivity.ENDPOINT, endpoint)
            fragment.arguments = args
            return fragment
        }
    }
}
