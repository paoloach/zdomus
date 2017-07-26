package it.achdjian.paolo.temperaturemonitor.domusEngine

/**
 * Created by Paolo Achdjian on 7/12/17.
 */
interface NewTemperatureDeviceListener {
    fun newTemperatureDevice(shortAddr: Int, endpointId: Int)
}