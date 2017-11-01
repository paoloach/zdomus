package it.achdjian.paolo.temperaturemonitor.dagger

import android.app.Application
import android.content.Context
import android.content.SharedPreferences
import android.preference.PreferenceManager
import dagger.Module
import dagger.Provides
import it.achdjian.paolo.temperaturemonitor.TempSensorLocationDS
import it.achdjian.paolo.temperaturemonitor.TemperatureCache
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionStatus
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domusEngine.rest.DomusEngineRest
import it.achdjian.paolo.temperaturemonitor.rajawali.Planes
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureRender
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureSurface
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 7/6/17.
 */
@Module
class TemperatureModule(val app: Application) {

    @Provides @Singleton @ForApplication
    fun provideApplicationContext(): Context {
        return app
    }

    @Provides @Singleton
    fun provideRender(rooms: Rooms,planes: Planes): TemperatureRender = TemperatureRender(app, rooms,planes )

    @Provides @Singleton
    fun provideSurface(render: TemperatureRender) = TemperatureSurface(app, render)

    @Provides @Singleton
    fun provideSharedPreferences() = PreferenceManager.getDefaultSharedPreferences(app)

    @Provides @Singleton
    fun provideDomusEngineRest(sharedPreferences: SharedPreferences, connectionStatus: ConnectionStatus) = DomusEngineRest(sharedPreferences, connectionStatus)

    @Provides @Singleton
    fun provideZDevices() = ZDevices()

    @Provides @Singleton
    fun provideDomusEngine(zDevices: ZDevices,
                           connectionStatus: ConnectionStatus,
                           tempSensorLocationDS: TempSensorLocationDS,
                           rooms: Rooms,
                           domusEngineRest: DomusEngineRest,
                           cache: TemperatureCache): DomusEngine {
        val domusEngine = DomusEngine(zDevices, connectionStatus, rooms, domusEngineRest)

        zDevices.domusEngine = domusEngine
        tempSensorLocationDS.domusEngine = domusEngine
        cache.domusEngine = domusEngine
        return domusEngine
    }
}