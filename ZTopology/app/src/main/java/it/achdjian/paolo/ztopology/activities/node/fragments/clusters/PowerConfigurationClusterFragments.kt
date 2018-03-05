package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.Cluster
import it.achdjian.paolo.ztopology.zigbee.Constants
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/26/18.
 */
class PowerConfigurationClusterFragments: ClusterFragment()  {
    override fun layoutResource() : Int = R.layout.power_configuration
    override fun clusterId() = Cluster.POWER_CONFIGURATION_CLUSTER

    companion object {
        fun newInstance(endpoint: ZEndpoint): PowerConfigurationClusterFragments {
            val fragment = PowerConfigurationClusterFragments()
            val args = Bundle()
            args.putSerializable(NodeActivity.ENDPOINT, endpoint)
            fragment.arguments = args
            return fragment
        }
    }
}