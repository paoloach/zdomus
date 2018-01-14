package it.achdjian.paolo.temperaturemonitor.graphic

import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.TemperatureDataJSON
import org.joda.time.LocalDateTime
import org.joda.time.format.ISODateTimeFormat

/**
 * Created by Paolo Achdjian on 10/31/17.
 */
class TemperatureData(json: TemperatureDataJSON) {
    val value = json.temperature.toFloat() / 100
    val time : LocalDateTime = dateTimeFormatter.parseLocalDateTime(json.time)
    val msTime get() = time.toDate().time

    companion object {
        val dateTimeFormatter = ISODateTimeFormat.basicDateTime();
    }


}