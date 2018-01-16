package it.achdjian.paolo.ztopology.domusEngine

import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import it.achdjian.paolo.ztopology.domusEngine.ConnectionObserver
import java.util.*
import kotlin.properties.Delegates

/**
 * Created by paolo on 14/04/16.
 */
object ConnectionStatus {
    private val observers = ArrayList<ConnectionObserver>()

    var connected: Boolean
            by Delegates.observable(false) {
                property, oldValue, new ->
                Log.i(ZigbeeRunnable.TAG, "old value: " + oldValue + " new value: " + new)
                if (oldValue != new) {
                    Log.i(ZigbeeRunnable.TAG, observers.size.toString() + " observers")
                    for (observer in observers) {
                        if (new)
                            observer.connected()
                        else
                            observer.disconnected()
                    }
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
