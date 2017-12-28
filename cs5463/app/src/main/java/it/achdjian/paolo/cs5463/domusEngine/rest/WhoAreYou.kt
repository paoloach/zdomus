package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.cs5463.domusEngine.ConnectionStatus
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.MessageType

/**
 * Created by Paolo Achdjian on 14/04/16.
 */
class WhoAreYou : ZigbeeRunnable(){
    companion object {
        private val EXPECTED_NAME = "I am DomusEngine"
    }


    override fun run() {
        try {
            Log.i(TAG,"Start who are you")
            val body = DomusEngineRest.get("/who_are_you")

            if (body.isNotBlank()) {
                if (body.substring(0, EXPECTED_NAME.length) == EXPECTED_NAME) {
                    ConnectionStatus.connected = true
                    Log.i(TAG,"Domus Engine found")
                    reschedule(300000)
                } else {
                    ConnectionStatus.connected = false
                    Log.i(TAG,"Domus Engine NOT found")
                    reschedule(10000)
                }
            } else {
                ConnectionStatus.connected = false
                reschedule(10000)
            }
        } catch (e: Exception) {
            ConnectionStatus.connected = false
            Log.i(TAG,"Domus Engine NOT found")
            reschedule(10000)
        }
    }

    private fun reschedule(delay: Long){

        DomusEngine.handler.removeMessages(MessageType.WHO_ARE_YOU)
        val message = DomusEngine.handler.obtainMessage(MessageType.WHO_ARE_YOU)
        if (delay==0L){
            DomusEngine.handler.sendMessage(message)
        } else {
            DomusEngine.handler.sendMessageDelayed(message, delay)
        }
    }

}
