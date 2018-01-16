package it.achdjian.paolo.ztopology.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest

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