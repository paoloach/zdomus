package it.achdjian.paolo.domusviewer;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import it.achdjian.paolo.domusviewer.devices.AllDevicesFragment_;
import it.achdjian.paolo.domusviewer.on_off.OnOffFragment_;
import it.achdjian.paolo.domusviewer.temperature.TemperatureFragment;
import it.achdjian.paolo.domusviewer.temperature.TemperatureFragment_;

/**
 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
public class SectionsPagerAdapter extends FragmentPagerAdapter {

    public SectionsPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    @Override
    public Fragment getItem(int position) {
        switch (position){
            case 0:
                return OnOffFragment_.builder().build();
            case  1:
                return AllDevicesFragment_.builder().build();
            case 2:
                return TemperatureFragment_.builder().build();
            default:
                return PlaceholderFragment.newInstance(position + 1);
        }
    }

    @Override
    public int getCount() {
        // Show 3 total pages.
        return 3;
    }

    @Override
    public CharSequence getPageTitle(int position) {
        switch (position) {
            case 0:
                return "On Off Binding";
            case 1:
                return "All devices";
            case 2:
                return "Temperature";
        }
        return null;
    }
}
