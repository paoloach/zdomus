package it.achdjian.paolo.temperaturemonitor.domus_engine_rest

import android.content.SharedPreferences
import android.os.Handler
import android.util.Log

/**
 * Created by Paolo Achdjian on 14/04/16.
 */
class WhoAreYou(val domusEngineRest: DomusEngineRest, val connectionStatus: ConnectionStatus) : Runnable,ConnectionObserver {


    private val TAG = WhoAreYou::class.java.name
    private val EXPECTED_NAME = "I am DomusEngine"
    private var stop=false
    private val lock = java.lang.Object()

    init {
        connectionStatus.addObserver(this)
    }


    fun forceCheck() = lock.notifyAll()
    fun forceStop() { stop=true}

    override fun run() {
        while (!stop) {
            try {
                val body = domusEngineRest.get("/who_are_you")
                if (body != null) {
                    if (body.substring(0, EXPECTED_NAME.length) == EXPECTED_NAME){
                        connectionStatus.connected =true
                        synchronized(lock){lock.wait(300000)}
                    } else {
                        connectionStatus.connected =false
                        synchronized(lock){lock.wait(10000)}
                    }
                } else {
                    domusEngineRest.connected.connected = false
                    synchronized(lock){lock.wait(10000)}
                }
            } catch (e:Exception) {
                domusEngineRest.connected.connected = false
                synchronized(lock){lock.wait(10000)}
            }

        }
    }

    override fun connected() {
    }

    override fun disconnected()  {
        synchronized(lock){lock.notifyAll()}
    }
}
