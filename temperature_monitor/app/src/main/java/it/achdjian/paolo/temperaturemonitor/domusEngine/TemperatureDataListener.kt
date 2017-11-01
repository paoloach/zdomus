package it.achdjian.paolo.temperaturemonitor.domusEngine

import it.achdjian.paolo.temperaturemonitor.graphic.TemperatureData

/**
 * Created by Paolo Achdjian on 10/31/17.
 */
interface TemperatureDataListener {
    fun newTemperatureData(data: List<TemperatureData> )
}