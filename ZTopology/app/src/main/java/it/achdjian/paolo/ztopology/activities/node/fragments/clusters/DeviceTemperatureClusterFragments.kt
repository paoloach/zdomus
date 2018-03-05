package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.Cluster
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/26/18.
 */
class DeviceTemperatureClusterFragments: ClusterFragment()  {
    override fun layoutResource() : Int = R.layout.device_temperature_cluster
    override fun clusterId() = Cluster.DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER

    companion object {
        fun newInstance(endpoint: ZEndpoint): DeviceTemperatureClusterFragments {
            val fragment = DeviceTemperatureClusterFragments()
            val args = Bundle()
            args.putSerializable(NodeActivity.ENDPOINT, endpoint)
            fragment.arguments = args
            return fragment
        }
    }
}