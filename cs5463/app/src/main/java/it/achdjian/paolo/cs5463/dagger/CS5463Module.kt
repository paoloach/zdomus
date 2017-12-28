package it.achdjian.paolo.cs5463.dagger

import android.content.SharedPreferences
import android.preference.PreferenceManager
import dagger.Module
import dagger.Provides
import it.achdjian.paolo.cs5463.domusEngine.ConnectionStatus
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.cs5463.zigbee.ZDevices
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 7/6/17.
 */
@Module
class CS5463Module(val application: CS5463Application) {

    @Provides
    @Singleton
    fun getSharedPreferences(): SharedPreferences {
        return PreferenceManager.getDefaultSharedPreferences(application)
    }
}