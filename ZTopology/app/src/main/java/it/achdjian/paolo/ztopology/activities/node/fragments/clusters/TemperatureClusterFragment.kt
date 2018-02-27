package it.achdjian.paolo.ztopology.activities.node.fragments.clusters

import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.NodeActivity
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

class TemperatureClusterFragment : Fragment() {

    private lateinit var zEndpoint: ZEndpoint


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        if (arguments != null) {
            zEndpoint = arguments.getSerializable(NodeActivity.ENDPOINT) as ZEndpoint
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater?, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        return inflater!!.inflate(R.layout.temperature_cluster, container, false)
    }

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
