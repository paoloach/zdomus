package it.achdjian.paolo.domusviewer.setting;

import android.os.Bundle;
import android.preference.PreferenceFragment;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by paolo on 14/04/16.
 */
public class SettingFragment extends PreferenceFragment{
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        addPreferencesFromResource(R.xml.preferences);
    }
}
