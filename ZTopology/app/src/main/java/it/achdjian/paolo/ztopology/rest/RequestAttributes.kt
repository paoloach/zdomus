package it.achdjian.paolo.ztopology.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType
import it.achdjian.paolo.ztopology.domusEngine.rest.Attribute
import it.achdjian.paolo.ztopology.domusEngine.rest.Attributes
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import it.achdjian.paolo.ztopology.zigbee.Cluster
import java.io.IOException

/**
 * Created by Paolo Achdjian on 2/27/18.
 */


class RequestAttributes(
    val nwkAddress: Int,
    val endpoint: Int,
    val cluster: Cluster,
    val attributes: List<Int>
) : ZigbeeRunnable() {
    override fun run() {
        if (attributes.size == 0)
            return
        val buffer = StringBuffer()
        attributes.forEach { buffer.append(it).append(",") }
        buffer.deleteCharAt(buffer.lastIndex)

        val path = "/devices/${nwkAddress.toString(16)}" +
                "/endpoint/${endpoint.toString(16)}" +
                "/cluster/in/${cluster.id.toString(16)}" +
                "/attributes?id=${buffer.toString()}"

        val body = DomusEngineRest.get(path)
        if (body.isNotBlank()) {
            try {
                Log.i(TAG, body)
                val jsonAttributes = MAPPER.readValue<List<Attribute>>(
                    body,
                    object : TypeReference<List<Attribute>>() {})
                val attributes = Attributes(nwkAddress, endpoint, cluster, jsonAttributes)
                DomusEngine.handler.sendMessage(
                    DomusEngine.handler.obtainMessage(MessageType.NEW_ATTRIBUTES, attributes )
                )
                Log.i(TAG, jsonAttributes.toString())
            } catch (e: IOException) {
                Log.e(TAG, "Error parsing response for $path")
                Log.e(TAG, "Response: $body")
                e.printStackTrace()
            }
        }
    }

}