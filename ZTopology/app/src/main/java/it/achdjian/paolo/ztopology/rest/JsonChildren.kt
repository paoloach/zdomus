package it.achdjian.paolo.ztopology.rest

/**
 * Created by Paolo Achdjian on 1/18/18.
 */
data class JsonChildren (val extendAddr: String, val nwkId: Int, val totalDevice: Int, val startIndex: Int, val children: List<Int> ){
}