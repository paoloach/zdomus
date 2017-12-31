package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import com.fasterxml.jackson.core.type.TypeReference
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.MessageType
import java.io.IOException

/**
 * Created by Paolo Achdjian on 12/28/17.
 */
class ExecuteCommand (val networkId: Int, val endpoint: Int, val cluster:Int, val cmdId:Int): ZigbeeRunnable()  {
    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(networkId, 16)).
                append("/endpoint/").
                append(Integer.toString(endpoint, 16)).
                append("/cluster/in/").
                append(Integer.toString(cluster, 16)).
                append("/command/").
                append(cmdId.toString(10))
        Log.d(TAG, builder.toString())
        DomusEngineRest.post(builder.toString())
    }
}