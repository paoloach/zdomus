package it.achdjian.paolo.temperaturemonitor.dagger

import android.app.Application
import android.content.Context
import android.content.SharedPreferences
import android.preference.PreferenceManager
import dagger.Module
import dagger.Provides
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.ConnectionStatus
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.DomusEngine
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.DomusEngineRest
import it.achdjian.paolo.temperaturemonitor.domus_engine_rest.WhoAreYou
import it.achdjian.paolo.temperaturemonitor.rajawali.Rooms
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureRender
import it.achdjian.paolo.temperaturemonitor.rajawali.TemperatureSurface
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
    fun provideRender(rooms:Rooms):TemperatureRender = TemperatureRender(app, rooms)

    @Provides @Singleton
    fun provideSurface(render: TemperatureRender) = TemperatureSurface(app,render)

    @Provides @Singleton
    fun provideRooms()= Rooms(app)

    @Provides @Singleton
    fun provideConnectionStatus() = ConnectionStatus()

    @Provides @Singleton 
    fun provideSharedPreferences() = PreferenceManager.getDefaultSharedPreferences(app)

    @Provides @Singleton
    fun provideWhoAreYou(domusEngineRest: DomusEngineRest, connectionStatus: ConnectionStatus) = WhoAreYou(domusEngineRest,connectionStatus )

    @Provides @Singleton
    fun provideDomusEngineRest(sharedPreferences:SharedPreferences, connectionStatus: ConnectionStatus) = DomusEngineRest(sharedPreferences,connectionStatus)

    @Provides @Singleton
    fun provideDomusEngine(whoAreYou: WhoAreYou) = DomusEngine(app.applicationContext,whoAreYou)
}