package it.achdjian.paolo.temperaturemonitor.domusEngine

import android.util.Log
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.ZigbeeRunnable
import java.util.*
import javax.inject.Inject
import javax.inject.Singleton
import kotlin.properties.Delegates

/**
 * Created by paolo on 14/04/16.
 */
@Singleton
class ConnectionStatus @Inject constructor(){
    private val observers = ArrayList<ConnectionObserver>()

    var connected: Boolean
            by Delegates.observable(false) {
                _, _, new ->
                Log.i(ZigbeeRunnable.TAG, "set new value: " + new)
                Log.i(ZigbeeRunnable.TAG, observers.size.toString() + " observers")
                for (observer in observers) {
                    if (new)
                        observer.connected()
                    else
                        observer.disconnected()
                }
            }

    fun addObserver(observer: ConnectionObserver) {
        Log.i(ZigbeeRunnable.TAG,"add observer")
        observers.add(observer)
    }

    fun removeObserver(observer: ConnectionObserver) {
        observers.remove(observer)
    }


}
