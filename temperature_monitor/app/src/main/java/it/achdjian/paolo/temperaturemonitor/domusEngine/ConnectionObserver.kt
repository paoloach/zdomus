package it.achdjian.paolo.temperaturemonitor.domusEngine

/**
 * Created by paolo on 14/04/16.
 */
interface ConnectionObserver {
    fun connected()
    fun disconnected()
}