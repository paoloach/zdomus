package it.achdjian.paolo.ztopology

/**
 * Created by Paolo Achdjian on 2/5/18.
 */
data class JsonNodeInfo(
    val nwkId: String,
    val logicalType: String,
    val bandFrequency: String,
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
        "2400",
        0, 0, 0, 0, 0, 0, 0
    ) {
    }
}



class NodeInfo (jsonValue: JsonNodeInfo){
    val nwkId = jsonValue.nwkId.toInt(16)
    val logicalType = toLogicalType(jsonValue.logicalType)
    val bandFrequency = toBandFrequency(jsonValue.bandFrequency)
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

enum class BandFrequency(val jsonValue: String){
    Mhz2400("2400"),
    Mhz900("900"),
    Mhz868("868")


}

fun toBandFrequency(value: String) : BandFrequency {
    return BandFrequency.values().firstOrNull{it.jsonValue == value}!!
}