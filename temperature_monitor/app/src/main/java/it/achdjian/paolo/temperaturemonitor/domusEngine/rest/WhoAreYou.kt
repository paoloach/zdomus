package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.os.Handler
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionObserver
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionStatus
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 14/04/16.
 */
class WhoAreYou @Inject constructor(
        val domusEngine: DomusEngine,
        val domusEngineRest: DomusEngineRest,
        val connectionStatus: ConnectionStatus) : ZigbeeRunnable(){
    companion object {
        private val EXPECTED_NAME = "I am DomusEngine"
    }


    override fun run() {
        try {
            Log.i(TAG,"Start who are you")
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

        domusEngine.handler.removeMessages(MessageType.WHO_ARE_YOU)
        val message = domusEngine.handler.obtainMessage(MessageType.WHO_ARE_YOU)
        if (delay==0L){
            domusEngine.handler.sendMessage(message)
        } else {
            domusEngine.handler.sendMessageDelayed(message, delay)
        }
    }

}
