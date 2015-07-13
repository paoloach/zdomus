package it.achdjian.domusviewer;

import android.content.res.AssetManager;
import android.support.annotation.NonNull;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import it.achdjian.domusviewer.View3D.View3DFragment;
import it.achdjian.domusviewer.ViewZigBee.ZigBeeFragment;

/**
 * Created by Paolo Achdjian on 03/07/15.
   Copyright Paolo Achdjian
 */
public class DomusPagerAdapter extends FragmentPagerAdapter {
    private static final String[] TITLES = {"view", "setup"};

	public DomusPagerAdapter(FragmentManager fm) {
        super(fm);
	}

    @Override
    @NonNull
    public Fragment getItem(int position) {
        switch (position){
            case 0:
                return new View3DFragment();
            case 1:
                return new ZigBeeFragment();
            default:
                return new View3DFragment();
        }
    }

    @Override
    public int getCount() {
        return 2;
    }

    @Override
    @NonNull
    public CharSequence getPageTitle(int position) {
        if (position >= 0 && position <= 1)
            return TITLES[position];
        else
            return  "";
    }
}
