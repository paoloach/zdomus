package it.achdjian.paolo.temperaturemonitor.settings

import android.app.Activity
import android.os.Bundle

/**
 * Created by Paolo Achdjian on 7/4/17.
 */
class SettingActivity : Activity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        fragmentManager.beginTransaction().replace(android.R.id.content, SettingFragment()).commit()

    }
}