package it.achdjian.paolo.temperaturemonitor.settings

import android.app.Activity
import android.os.Bundle
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.dagger.TemperatureApplication
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.MessageType
import javax.inject.Inject

/**
 * Created by Paolo Achdjian on 7/4/17.
 */
class SettingActivity : Activity() {
    @Inject
    lateinit var domusEngine: DomusEngine

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        (application as TemperatureApplication).component.inject(this)
+
        fragmentManager.beginTransaction().replace(android.R.id.content, SettingFragment()).commit()
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.i("INIT", "request who are you")
        val message = domusEngine.handler.obtainMessage(MessageType.WHO_ARE_YOU)
        domusEngine.handler.sendMessage(message)

    }
}