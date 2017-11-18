package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import com.fasterxml.jackson.core.type.TypeReference
import com.fasterxml.jackson.databind.ObjectMapper
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import it.achdjian.paolo.temperaturemonitor.graphic.TemperatureData
import org.joda.time.LocalDateTime
import org.joda.time.format.DateTimeFormat

/**
 * Created by Paolo Achdjian on 10/31/17.
 */
class GetTemperatures(val networkId: Int, val start:LocalDateTime, val end: LocalDateTime, val domusEngine: DomusEngine, val domusEngineRest: DomusEngineRest) : ZigbeeRunnable() {
    companion object {
        val DATE_FORMAT = "yyyy-MM-dd%20HH:mm:ss"
        val dateTimeFormatter = DateTimeFormat.forPattern(DATE_FORMAT)
        val mapper = ObjectMapper()
    }

    override fun run() {
        val buffer = StringBuffer("/temperature/").append(networkId).append("?dataFrom=")
        dateTimeFormatter.printTo(buffer, start)
        buffer.append("&dataTo=")
        dateTimeFormatter.printTo(buffer, end)

        val body = domusEngineRest.get(buffer.toString())
        if (body.isNotBlank()) {
            val json = mapper.readValue<List<TemperatureDataJSON>>(body, object : TypeReference<List<TemperatureDataJSON>>() {
            })
            val data = json.map { TemperatureData(it) }.filter { it.value < 50 }
            domusEngine.handler.sendMessage(domusEngine.handler.obtainMessage(MessageType.NEW_DATA_TEMPERATURES, data))
        }

    }
}