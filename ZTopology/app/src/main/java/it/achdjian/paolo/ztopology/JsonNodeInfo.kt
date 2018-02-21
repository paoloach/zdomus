package it.achdjian.paolo.ztopology

/**
 * Created by Paolo Achdjian on 2/5/18.
 */
data class JsonNodeInfo(
    val nwkId: String,
    val logicalType: String,
    val bandFrequency: Int,
    val macCapability: Int,
    val manufactorerCode: Int,
    val maximumBufferSize: Int,
    val maximumIncomingTransferSize: Int,
    val serverMask: Int,
    val maximumOutcomingTransferSize: Int,
    val descriptorCapability: Int
) {
    constructor() : this(
        "FF-FF-FF-FF-FF-FF-FF-FF",
        "end device",
        0x08,
        0, 0, 0, 0, 0, 0, 0
    ) {
    }
}



class NodeInfo (jsonValue: JsonNodeInfo){
    val nwkId = jsonValue.nwkId.toInt(16)
    val logicalType = toLogicalType(jsonValue.logicalType)
    val bandFrequency = BandFrequency(jsonValue.bandFrequency)
    val macCapability = jsonValue.macCapability
    val manufactorerCode = jsonValue.manufactorerCode
    val maximumBufferSize = jsonValue.maximumBufferSize
    val maximumIncomingTransferSize = jsonValue.maximumIncomingTransferSize
    val serverMask = jsonValue.serverMask
    val maximumOutcomingTransferSize = jsonValue.maximumOutcomingTransferSize
    val descriptorCapability = jsonValue.descriptorCapability

}

enum class LogicalType(val jsonValue: String) {
    ZigbeeCordinator("coordinator"),
    ZigbeeRouter("router"),
    ZigbeeEnddevice("end device"),
    Invalid("invalid")
}

fun toLogicalType(value: String) : LogicalType {
    return LogicalType.values().firstOrNull{it.jsonValue == value}!!
}

class BandFrequency(val value: Int){

    fun has868Mhz() = value and 0x01;
    fun has913Mhz() = value and 0x02;
    fun has2400Mhz() = value and 0x08;

}
