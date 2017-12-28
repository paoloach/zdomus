package it.achdjian.paolo.cs5463

import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentPagerAdapter
import dagger.android.DispatchingAndroidInjector
import it.achdjian.paolo.cs5463.dagger.DaggerMeasureRegistersFragmentComponent
import it.achdjian.paolo.cs5463.dagger.FragmentModule
import javax.inject.Inject

/**
 * Created by Paolo Achdjian on 11/21/17.
 */
class SectionsPageAdapter @Inject constructor(fm: FragmentManager) : FragmentPagerAdapter(fm) {

    override fun getItem(position: Int): Fragment {
        when(position){
            0 -> return StatusRegisterFragment.newInstance()
            1 -> return MeasureRegistersFragment.newInstance()
        }
        return MeasureRegistersFragment.newInstance()
    }

    override fun getCount(): Int {
        return 2
    }

    override fun getPageTitle(position: Int): CharSequence? {
        when (position){
            0 -> return "configuration"
            1 -> return "measure register"
        }
        return null
    }
}