package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.util.Log

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