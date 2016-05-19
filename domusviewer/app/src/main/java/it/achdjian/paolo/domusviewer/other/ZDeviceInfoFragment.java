package it.achdjian.paolo.domusviewer.other;

import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.ListView;
import android.widget.TextView;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.FragmentArg;
import org.androidannotations.annotations.ViewById;

import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 11/05/16.
 */
@EFragment(R.layout.zdevice_info)
public class ZDeviceInfoFragment extends DialogFragment implements DomusEngine.AttributesListener {
    @FragmentArg("network_id")
    Integer networkId;
    @FragmentArg("endpoint_id")
    Integer endpointId;


    @ViewById(R.id.name)
    TextView name;
    @ViewById(R.id.model)
    TextView model;
    @ViewById(R.id.date)
    TextView date;
    @ViewById(R.id.location)
    TextView location;
    @ViewById(R.id.environment)
    TextView environment;
    @ViewById(R.id.enabled)
    CheckBox checkBox;
    @Bean
    DomusEngine domusEngine;

    @AfterViews
    public void afterView(){
        domusEngine.requestAttributes(this,networkId, endpointId, 0,4,5,6,0x10,0x11,0x12);
    }

    @Override
    public void newAttributes(List<JSonAttribute> attributes) {

    }
}
