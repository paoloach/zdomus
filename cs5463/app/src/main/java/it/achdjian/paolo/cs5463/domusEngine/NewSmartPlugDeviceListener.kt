package it.achdjian.paolo.cs5463.domusEngine

/**
 * Created by Paolo Achdjian on 7/12/17.
 */
interface NewSmartPlugDeviceListener {
    fun newSmartPlugDevice(shortAddr: Int, endpointId: Int)
}