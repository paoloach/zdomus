package it.achdjian.paolo.ztopology.activities.node

import android.support.design.widget.TabLayout
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.activities.node.fragments.clusters.*
import it.achdjian.paolo.ztopology.zigbee.Cluster
import it.achdjian.paolo.ztopology.zigbee.ZEndpoint
import it.achdjian.paolo.ztopology.zigbee.idToCluster

/**
 * Created by Paolo Achdjian on 2/27/18.
 */
class ClusterTabSelectedListener(private val supportFragmentManager: FragmentManager ) : TabLayout.OnTabSelectedListener {
    var zEndpoint: ZEndpoint? = null
    override fun onTabReselected(tab: TabLayout.Tab?) {
    }

    override fun onTabUnselected(tab: TabLayout.Tab?) {
    }

    override fun onTabSelected(tab: TabLayout.Tab?) {
        val zEndpoint = this.zEndpoint
        if (zEndpoint != null && tab != null){
            val cluster = tab.tag as Cluster
            supportFragmentManager.beginTransaction()
                .replace(R.id.container, fragmentFromCluster(cluster, zEndpoint))
                .commit()
        }
    }

    private fun fragmentFromCluster(clusterId: Cluster, zEndpoint: ZEndpoint): Fragment {
        when (clusterId){
            Cluster.BASIC_CLUSTER -> return BasicClusterFragments.newInstance(zEndpoint)
            Cluster.POWER_CONFIGURATION_CLUSTER -> return PowerConfigurationClusterFragments.newInstance(zEndpoint)
            Cluster.DEVICE_TEMPERATURE_CONFIGURATION_CLUSTER -> return DeviceTemperatureClusterFragments.newInstance(zEndpoint)
            Cluster.IDENTIFY_CLUSTER -> return IdentifyClusterFragment.newInstance(zEndpoint)
            Cluster.GROUPS_CLUSTER -> return GroupsClusterFragments.newInstance(zEndpoint)
            Cluster.SCENES_CLUSTER -> return ScenesClusterFragments.newInstance(zEndpoint)
            Cluster.ON_OFF_CLUSTER -> return OnOffClusterFragment.newInstance(zEndpoint)
            Cluster.TEMPERATURE_MEASUREMENT ->return TemperatureClusterFragment.newInstance(zEndpoint)
        }
        return BasicClusterFragments.newInstance(zEndpoint)
    }
}