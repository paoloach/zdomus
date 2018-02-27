package it.achdjian.paolo.ztopology.activities.node

import android.support.design.widget.TabLayout
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.node.fragments.clusters.BasicClusterFragments
import it.achdjian.paolo.ztopology.activities.node.fragments.clusters.IdentifyClusterFragment
import it.achdjian.paolo.ztopology.activities.node.fragments.clusters.TemperatureClusterFragment
import it.achdjian.paolo.ztopology.zigbee.Constants.BASIC_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.IDENTIFY_CLUSTER
import it.achdjian.paolo.ztopology.zigbee.Constants.TEMPERATURE_MEASUREMENT
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint

/**
 * Created by Paolo Achdjian on 2/27/18.
 */
class ClusterTabSelectedListener(val supportFragmentManager: FragmentManager ) : TabLayout.OnTabSelectedListener {
    var zEndpoint: ZEndpoint? = null
    override fun onTabReselected(tab: TabLayout.Tab?) {
    }

    override fun onTabUnselected(tab: TabLayout.Tab?) {
    }

    override fun onTabSelected(tab: TabLayout.Tab?) {
        val zEndpoint = this.zEndpoint
        if (zEndpoint != null && tab != null){
            val clusterId = tab.tag as Int
            supportFragmentManager.beginTransaction()
                .replace(R.id.container, fragmentFromCluster(clusterId, zEndpoint))
                .commit()
        }
    }

    private fun fragmentFromCluster(clusterId: Int, zEndpoint: ZEndpoint): Fragment {
        when (clusterId){
            BASIC_CLUSTER -> return BasicClusterFragments.newInstance(zEndpoint)
            IDENTIFY_CLUSTER -> return IdentifyClusterFragment.newInstance(zEndpoint)
            TEMPERATURE_MEASUREMENT ->return TemperatureClusterFragment.newInstance(zEndpoint)
        }
        return BasicClusterFragments.newInstance(zEndpoint)
    }
}