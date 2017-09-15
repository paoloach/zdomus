package it.achdjian.paolo.temperaturemonitor.dagger

import dagger.Component
import it.achdjian.paolo.temperaturemonitor.MainActivity
import it.achdjian.paolo.temperaturemonitor.TempSensorLocationDS
import it.achdjian.paolo.temperaturemonitor.TemperatureCache
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionStatus
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.PowerListener
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureRender
import it.achdjian.paolo.temperaturemonitor.ui.*
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

    fun getAssignController(): AssignController
    fun getDeassignController(): DeassignController
    fun getZElementAdapter(): ZElementAdapter
    fun getTemperatureCache(): TemperatureCache
    fun getRooms(): Rooms
    fun getElements(): Elements
    fun getTempSensorLocationDS(): TempSensorLocationDS
    fun getAssignButtons(): AssigningButtons
    fun getConnectionStatus(): ConnectionStatus
    fun getInitRoom(): InitRoom
    fun getListViewShowing(): ListViewShowing
    fun getSwipeListView(): SwipeListView
    fun getIdentifyListener(): IdentifyListener
    fun getPowerUpdateView(): PowerUpdateView

}