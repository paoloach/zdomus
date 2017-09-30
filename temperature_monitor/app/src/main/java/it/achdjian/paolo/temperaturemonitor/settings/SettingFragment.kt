package it.achdjian.paolo.temperaturemonitor.settings

import android.os.Bundle
import android.preference.PreferenceFragment
import it.achdjian.paolo.temperaturemonitor.R

/**
 * Created by Paolo Achdjian on 7/4/17.
 */
class SettingFragment : PreferenceFragment() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        addPreferencesFromResource(R.xml.preferences)
    }
}