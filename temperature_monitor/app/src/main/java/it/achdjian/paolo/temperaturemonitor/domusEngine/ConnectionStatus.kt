package it.achdjian.paolo.temperaturemonitor.domusEngine

import java.util.*
import kotlin.properties.Delegates

/**
 * Created by paolo on 14/04/16.
 */
class ConnectionStatus {
    private val observers = ArrayList<ConnectionObserver>()

    var connected: Boolean by Delegates.observable(false) {
        _, _, new ->
        for (observer in observers) {
            if (new)
                observer.connected()
            else
                observer.disconnected()
        }
    }

    fun addObserver(observer: ConnectionObserver) {
        observers.add(observer)
    }

    fun removeObserver(observer: ConnectionObserver) {
        observers.remove(observer)
    }


}
