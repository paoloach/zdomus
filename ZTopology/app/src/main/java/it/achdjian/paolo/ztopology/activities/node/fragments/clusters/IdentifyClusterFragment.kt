package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/27/18.
 */
class IdentifyClusterFragment: Fragment()   {
    lateinit var endpoint: ZEndpoint

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val rootView = inflater.inflate(R.layout.identify_cluster, container, false)
        if (arguments != null && arguments.getSerializable(NodeActivity.ENDPOINT) != null) {
            endpoint = arguments.getSerializable(NodeActivity.ENDPOINT) as ZEndpoint
        }

        return rootView
    }

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