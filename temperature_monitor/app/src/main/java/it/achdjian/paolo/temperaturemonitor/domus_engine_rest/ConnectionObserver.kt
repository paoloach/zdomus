package it.achdjian.paolo.temperaturemonitor.domus_engine_rest

/**
 * Created by paolo on 14/04/16.
 */
interface ConnectionObserver {
    fun connected()
    fun disconnected()
}