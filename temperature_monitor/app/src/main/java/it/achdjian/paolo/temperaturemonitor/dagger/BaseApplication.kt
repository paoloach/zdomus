package it.achdjian.paolo.temperaturemonitor.dagger

import android.app.Application

/**
 * Created by Paolo Achdjian on 7/6/17.
 */
abstract class BaseApplication : Application() {
    protected fun initDaggerComponent(): ApplicationComponent {
        return DaggerApplicationComponent.builder().temperatureModule(TemperatureModule(this)).build()
    }
}