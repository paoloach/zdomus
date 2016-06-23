package it.achdjian.paolo.domusviewer.devices;

import android.support.v4.app.Fragment;
import android.widget.ListView;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.ViewById;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 21/06/16.
 */
@EFragment(R.layout.all_devices)
public class AllDevicesFragment extends Fragment {
    @ViewById(R.id.listDevices)
    ListView devices;
    @Bean
    DomusEngine domusEngine;
    @Bean
    DeviceAdapter deviceAdapter;


    @AfterViews
    public void afterView(){
        deviceAdapter.init();

        devices.setAdapter(deviceAdapter);
    }

}
