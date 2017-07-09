package it.achdjian.paolo.temperaturemonitor.zigbee

import java.util.HashMap

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class ZEndpoint(val shortAddress: Int, val id: Int, val profileId: Int, val deviceId: Int, val deviceVersion: Int) {
    val input_clusters: Map<Int, Int> = HashMap()
    val output_clusters: Map<Int, Int> = HashMap()
    fun containsOutCluster(cluster: Int): Boolean {
        for (clusterID in output_clusters.values) {
            if (clusterID === cluster) {
                return true
            }
        }
        return false
    }

    fun containsInCluster(cluster: Int): Boolean {
        for (clusterID in input_clusters.values) {
            if (clusterID === cluster) {
                return true
            }
        }
        return false
    }

}