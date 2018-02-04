package it.achdjian.paolo.ztopology.rest

/**
 * Created by Paolo Achdjian on 1/29/18.
 */
data class JSonDeviceInfo(val nwkAddr: String,
                          val nodeRelation: String,
                          val devStatus: String,
                          val assocCnt: Int,
                          val age: Int,
                          val txCounter: Int,
                          val txCost: Int,
                          val rxLqi: Int) {
    constructor():this("FFFF","0", "0",0,0,0,0,0)
}

class DeviceInfo(jSonDeviceInfo: JSonDeviceInfo){
    val nwkAddr = jSonDeviceInfo.nwkAddr.toInt(16)
    val nodeRelation = jSonDeviceInfo.nodeRelation.toInt()
    val devStatus = jSonDeviceInfo.devStatus.toInt()
    val assocCnt = jSonDeviceInfo.assocCnt
    val age = jSonDeviceInfo.age
    val txCounter = jSonDeviceInfo.txCounter
    val txCost = jSonDeviceInfo.txCost
    val rxLqi = jSonDeviceInfo.rxLqi
}