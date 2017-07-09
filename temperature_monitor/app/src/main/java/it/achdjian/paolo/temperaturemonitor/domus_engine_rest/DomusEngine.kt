package it.achdjian.paolo.temperaturemonitor.domus_engine_rest

import android.content.Context
import android.os.Handler
import android.os.HandlerThread

/**
 * Created by Paolo Achdjian on 7/9/17.
 */
class DomusEngine(val context: Context, val whoAreYou: WhoAreYou) : HandlerThread("DomusEngtine") {
    init {
        start()
        val handler = Handler(looper)
        handler.post(whoAreYou)
    }
}