package it.achdjian.paolo.ztopology.rest

/**
 * Created by Paolo Achdjian on 1/18/18.
 */
data class JsonChildren (val extendAddr: String, val nwkId: String, val totalDevice: Int, val startIndex: Int, val children: List<String> ){
    constructor() : this("FF-FF-FF-FF-FF-FF-FF-FF", "FFFF", 0, 0, ArrayList<String>()){
    }
}

class Children(jsonChildren:JsonChildren){
    val extendAddr = jsonChildren.extendAddr
    val nwkId = jsonChildren.nwkId.toInt(16)
    val startIndex = jsonChildren.startIndex
    val children = jsonChildren.children.map {it.toInt(16) }
}