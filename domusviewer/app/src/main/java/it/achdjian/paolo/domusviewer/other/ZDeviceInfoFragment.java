package it.achdjian.paolo.domusviewer.other;

import android.support.v4.app.DialogFragment;
import android.widget.CheckBox;
import android.widget.TextView;

import org.androidannotations.annotations.AfterViews;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EFragment;
import org.androidannotations.annotations.FragmentArg;
import org.androidannotations.annotations.UiThread;
import org.androidannotations.annotations.ViewById;

import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.DomusEngineRest.Stoppable;
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
    Stoppable request;

    @AfterViews
    public void afterView(){

        getDialog().setTitle("device "+networkId + " endpoint " + endpointId);
        name.setText("");
        model.setText("");
        date.setText("");
        location.setText("");
        environment.setText("");
        checkBox.setChecked(false);
        request = domusEngine.requestAttributes(this, networkId, endpointId, 0, 4, 5, 6, 0x10, 0x11, 0x12);
    }

    @Override
    public void onDestroyView(){
        if (request != null){
            request.stop();
        }
        super.onDestroyView();
    }

    @Override
    @UiThread
    public void newAttributes(List<JSonAttribute> attributes) {
        for (JSonAttribute attribute : attributes) {
            if (attribute.isSupported && attribute.isAvailable) {
                switch (attribute.id) {
                    case 4:
                        name.setText(attribute.value);
                        break;
                    case 5:
                        model.setText(attribute.value);
                        break;
                    case 6:
                        date.setText(attribute.value);
                        break;
                    case 0x10:
                        location.setText(attribute.value);
                        break;
                    case 0x11:
                        environment.setText(attribute.value);
                        break;
                    case 0x12:
                        checkBox.setChecked(attribute.value.equals("1"));
                        break;
                }
            }
        }
    }
}
