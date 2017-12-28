package it.achdjian.paolo.cs5463.dagger

import android.content.SharedPreferences
import android.preference.PreferenceManager
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v7.app.AppCompatActivity
import dagger.Component
import dagger.Module
import dagger.Provides
import it.achdjian.paolo.cs5463.MainActivity
import it.achdjian.paolo.cs5463.MeasureRegistersFragment
import it.achdjian.paolo.cs5463.Register.LoadRegister
import it.achdjian.paolo.cs5463.Register.Register2View
import it.achdjian.paolo.cs5463.Register.RegistersValue
import it.achdjian.paolo.cs5463.RegistersAdapter
import it.achdjian.paolo.cs5463.SectionsPageAdapter
import it.achdjian.paolo.cs5463.domusEngine.ConnectionStatus
import it.achdjian.paolo.cs5463.domusEngine.DomusEngine
import it.achdjian.paolo.cs5463.zigbee.ZDevices
import javax.inject.Singleton


@Module
object StaticModule{
    @JvmStatic
    @Provides
    @Singleton
    fun fragmentManager(mainActivity: AppCompatActivity): FragmentManager {
        return mainActivity.supportFragmentManager
    }
}

@Singleton
@Component(modules = arrayOf(CS5463Module::class))
interface ApplicationComponent {
}


@Module
class MainActivityModule(val mainActivity: MainActivity) {
    @Provides
    @Singleton
    fun fragmentManager(): FragmentManager {
        return mainActivity.supportFragmentManager;
    }

}

@Singleton
@Component(modules = arrayOf(CS5463Module::class, MainActivityModule::class))
interface MainActivityComponent {
    fun inject(mainActivity: MainActivity)
    fun sectionsPageAdapter(): SectionsPageAdapter
}

@Module
class FragmentModule(val fragment:Fragment){
    @Provides
    @Singleton
    fun getSharedPreferences(): SharedPreferences {
        return PreferenceManager.getDefaultSharedPreferences(fragment.activity.application)
    }

    @Provides
    @Singleton
    fun mainActivity(): MainActivity {
        return fragment.activity as MainActivity
    }
}

@Singleton
@Component(modules = arrayOf(FragmentModule::class))
interface MeasureRegistersFragmentComponent{
    fun inject(fragment: MeasureRegistersFragment)
    fun loadRegister(): LoadRegister
    fun registerValue(): RegistersValue
    fun registersAdapter(): RegistersAdapter
    fun register2View(): Register2View
}