package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.cs5463.domusEngine.rest.ZigbeeRunnable

/**
 * Created by Paolo Achdjian on 8/23/17.
 */
class RequestIdentify (val networkdId: Int, val endpointId: Int, val domusEngineRest: DomusEngineRest): ZigbeeRunnable() {
    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(networkdId, 16)).
                append("/endpoint/").
                append(Integer.toString(endpointId, 16)).
                append("/cluster/in/3/command/0")
        Log.d(TAG, builder.toString())
        domusEngineRest.post(builder.toString())
    }
}