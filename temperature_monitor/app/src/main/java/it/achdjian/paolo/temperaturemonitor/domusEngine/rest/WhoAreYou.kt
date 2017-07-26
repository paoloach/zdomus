package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.os.Handler
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionObserver
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionStatus
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType

/**
 * Created by Paolo Achdjian on 14/04/16.
 */val handler = Handler()
class WhoAreYou(val domusEngineRest: DomusEngineRest, val connectionStatus: ConnectionStatus) : ZigbeeRunnable(), ConnectionObserver {
    companion object {
        private val EXPECTED_NAME = "I am DomusEngine"
    }

    init {
        connectionStatus.addObserver(this)
    }

    override fun run() {
        try {
            val body = domusEngineRest.get("/who_are_you")
            if (body.isNotBlank()) {
                if (body.substring(0, EXPECTED_NAME.length) == EXPECTED_NAME) {
                    connectionStatus.connected = true
                    Log.i(TAG,"Domus Engine found")
                    reschedule(300000)
                } else {
                    connectionStatus.connected = false
                    Log.i(TAG,"Domus Engine NOT found")
                    reschedule(10000)
                }
            } else {
                domusEngineRest.connected.connected = false
                reschedule(10000)
            }
        } catch (e: Exception) {
            domusEngineRest.connected.connected = false
            Log.i(TAG,"Domus Engine NOT found")
            reschedule(10000)
        }
    }

    private fun reschedule(delay: Long){

        handler.removeMessages(MessageType.WHO_ARE_YOU)
        val message = handler.obtainMessage(MessageType.WHO_ARE_YOU)
        if (delay==0L){
            handler.sendMessage(message)
        } else {
            handler.sendMessageDelayed(message, delay)
        }
    }

    override fun connected() {
    }

    override fun disconnected() {
        reschedule(1000L)
    }
}
