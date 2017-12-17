package it.achdjian.paolo.cs5463.dagger

import android.app.Application


/**
 * Created by Paolo Achdjian on 7/6/17.
 */
class CS5463Application : Application () {

    override fun onCreate() {
        super.onCreate()
        DaggerApplicationComponent.builder().cS5463Module(CS5463Module(this)).build()
    }

}
