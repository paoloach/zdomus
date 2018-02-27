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
 * Created by Paolo Achdjian on 2/26/18.
 */
class BasicClusterFragments: Fragment()  {
    lateinit var endpoint: ZEndpoint

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val rootView = inflater.inflate(R.layout.basic_cluster, container, false)
        if (arguments != null && arguments.getSerializable(NodeActivity.ENDPOINT) != null) {
            endpoint = arguments.getSerializable(NodeActivity.ENDPOINT) as ZEndpoint
        }

        return rootView
    }

    companion object {
        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        fun newInstance(endpoint: ZEndpoint): BasicClusterFragments {
            val fragment = BasicClusterFragments()
            val args = Bundle()
            args.putSerializable(NodeActivity.ENDPOINT, endpoint)
            fragment.arguments = args
            return fragment
        }
    }
}