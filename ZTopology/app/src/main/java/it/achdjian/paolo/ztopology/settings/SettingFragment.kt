package it.achdjian.paolo.ztopology.settings

import android.os.Bundle
import android.preference.PreferenceFragment
import android.preference.PreferenceManager
import it.achdjian.paolo.ztopology.R
import it.achdjian.paolo.ztopology.domusEngine.rest.DomusEngineRest

/**
 * Created by Paolo Achdjian on 7/4/17.
 */
class SettingFragment : PreferenceFragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        addPreferencesFromResource(R.xml.preferences)
    }

    override fun onDestroy() {
        super.onDestroy()
        DomusEngineRest.address = PreferenceManager.getDefaultSharedPreferences(this.activity).getString("DomusEngineAddress", "192.168.1.121:8080")
    }
}