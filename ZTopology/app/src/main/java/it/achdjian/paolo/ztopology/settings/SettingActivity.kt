package it.achdjian.paolo.ztopology.settings

import android.app.Activity
import android.os.Bundle
import android.util.Log
import it.achdjian.paolo.ztopology.settings.SettingFragment
import it.achdjian.paolo.ztopology.DomusEngine
import it.achdjian.paolo.ztopology.MessageType

/**
 * Created by Paolo Achdjian on 7/4/17.
 */
class SettingActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        fragmentManager.beginTransaction().replace(android.R.id.content, SettingFragment()).commit()
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.i("INIT", "request who are you")
        val message = DomusEngine.handler.obtainMessage(MessageType.WHO_ARE_YOU)
        DomusEngine.handler.sendMessage(message)
    }
}