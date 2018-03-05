package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.Cluster
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/26/18.
 */
class OnOffClusterFragment: ClusterFragment()  {
    override fun layoutResource() : Int = R.layout.on_off_cluster
    override fun clusterId() = Cluster.ON_OFF_CLUSTER

    companion object {
        fun newInstance(endpoint: ZEndpoint): OnOffClusterFragment {
            val fragment = OnOffClusterFragment()
            val args = Bundle()
            args.putSerializable(NodeActivity.ENDPOINT, endpoint)
            fragment.arguments = args
            return fragment
        }
    }
}