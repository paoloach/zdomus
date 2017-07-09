package it.achdjian.paolo.temperaturemonitor.dagger

/**
 * Created by Paolo Achdjian on 7/6/17.
 */
class TemperatureApplication : BaseApplication() {
    lateinit var component: ApplicationComponent

    override fun onCreate() {
        super.onCreate()
        val component = initDaggerComponent()
        component.inject(this)
        this.component = component
    }
}