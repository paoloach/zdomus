package it.achdjian.paolo.temperaturemonitor.dagger

import dagger.Component
import it.achdjian.paolo.temperaturemonitor.MainActivity
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureRender
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 7/6/17.
 */

@Singleton
@Component(modules = arrayOf(TemperatureModule::class))
interface ApplicationComponent {
    fun inject(application: BaseApplication)
    fun inject(activity: MainActivity)
    fun inject(renderer: TemperatureRender)

}