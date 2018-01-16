package it.achdjian.paolo.ztopology.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.ztopology.domusEngine.rest.ZigbeeRunnable
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest

/**
 * Created by Paolo Achdjian on 8/23/17.
 */
class RequestIdentify (val networkdId: Int, val endpointId: Int): ZigbeeRunnable() {
    override fun run() {
        val builder = StringBuilder("/devices/").
                append(Integer.toString(networkdId, 16)).
                append("/endpoint/").
                append(Integer.toString(endpointId, 16)).
                append("/cluster/in/3/command/0")
        Log.d(TAG, builder.toString())
        DomusEngineRest.post(builder.toString())
    }
}