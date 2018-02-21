package it.achdjian.paolo.ztopology.rest

import it.achdjian.paolo.ztopology.toLogicalType

/**
 * Created by Paolo Achdjian on 2/19/18.
 */

data class JsonLQITable(
    val panAddr: String,
    val ieeeAddr: String,
    val nwkId: String,
    val logicalType: String,
    val onWhenIdle: Boolean,
    val relationship: String,
    val neighborAcceptJoin: Boolean,
    val depth: Int,
    val lqi: Int,
    val index: Int
) {
    constructor() : this("", "", "", "", false, "", false, 0, 0, 0)
}

data class JsonLQI(val nwkAddrOwner: String, val totalTables: Int, val tables: List<JsonLQITable>) {
    constructor() : this("", 0, emptyList<JsonLQITable>())
}

class LQITable(table: JsonLQITable) {
    val extAddr = table.ieeeAddr
    val panAddr = table.panAddr
    val nwkAddr = table.nwkId.toInt(16)
    val logicalType = toLogicalType(table.logicalType)
    val onWhenIdle = table.onWhenIdle
    val relationship = toRelationship(table.relationship)
    val depth = table.depth
    val lqi = table.lqi
    val index = table.index
}

class LQI(lqi: JsonLQI) {
    val nwkAddrOwner = lqi.nwkAddrOwner.toInt(16)
    val totTable = lqi.totalTables
    val tables = lqi.tables.map { LQITable(it) }
}

enum class Relationship(val jsonValue: String) {
    NeighborIsParent("NeighborIsParent"),
    NeighborIsChild("NeighborIsChild"),
    NeighborIsSibling("NeighborIsSibling"),
    NoRelation("NoRelation"),
    PreviousChild("PreviousChild"),
    Invalid("Invalid")

}

fun toRelationship(value: String): Relationship {
    return Relationship.values().firstOrNull { it.jsonValue == value }!!
}