package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.Constants
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/27/18.
 */
class IdentifyClusterFragment : ClusterFragment() {
    override fun layoutResource(): Int = R.layout.identify_cluster
    override fun clusterId(): Int = Constants.IDENTIFY_CLUSTER

    companion object {
        fun newInstance(endpoint: ZEndpoint): IdentifyClusterFragment {
            val fragment = IdentifyClusterFragment()
            val args = Bundle()
            args.putSerializable(NodeActivity.ENDPOINT, endpoint)
            fragment.arguments = args
            return fragment
        }
    }
}