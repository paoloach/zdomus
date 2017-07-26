package it.achdjian.paolo.temperaturemonitor.zigbee

import java.util.HashMap

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class ZEndpoint(val short_address: Int, val endpoint_id: String, val profile_id: Int, val device_id: Int, val device_version: Int) {
    constructor():this(0,"0",0,0,0){}
    var input_clusters: Map<Int, Int> = HashMap()
    var output_clusters: Map<Int, Int> = HashMap()
    fun containsOutCluster(cluster: Int): Boolean {
        for (clusterID in output_clusters.values) {
            if (clusterID == cluster) {
                return true
            }
        }
        return false
    }

    fun containsInCluster(cluster: Int): Boolean {
        for (clusterID in input_clusters.values) {
            if (clusterID == cluster) {
                return true
            }
        }
        return false
    }

}