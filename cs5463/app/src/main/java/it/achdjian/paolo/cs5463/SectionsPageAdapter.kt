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
        val fragment = MeasureRegistersFragment.newInstance()
        return  fragment
    }

    override fun getCount(): Int {
        return 3
    }

    override fun getPageTitle(position: Int): CharSequence? {
        when (position){
            0 -> return "configuration"
            1 -> return "mode"
            2 -> return "measure register"
        }
        return null
    }
}