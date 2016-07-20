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

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DTO.WriteAttributeRequest;
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
    private Stoppable request;
    private String prevLocation;

    @AfterViews
    public void afterView() {

        getDialog().setTitle("device " + networkId + " endpoint " + endpointId);
        prevLocation="";
        name.setText("");
        model.setText("");
        date.setText("");
        location.setText("");
        environment.setText("");
        checkBox.setChecked(false);
        request = domusEngine.requestAttributes(this, networkId, endpointId, Constants.BASIC_CLUSTER,
                Constants.MANUFACTURER_NAME,
                Constants.MODEL_IDENTIFIER,
                Constants.DATE_CODE,
                Constants.LOCATION_DESCRIPTION,
                Constants.PHYSICAL_ENVIRONMENT,
                Constants.DEVICE_ENABLED);
    }

    @Override
    public void onPause(){
        String actualLocation = location.getText().toString();
        if (!actualLocation.equals(prevLocation)){
            WriteAttributeRequest writeAttributeRequest =new WriteAttributeRequest();
            writeAttributeRequest.networkId = networkId;
            writeAttributeRequest.endpointId = endpointId;
            writeAttributeRequest.clusterId = Constants.BASIC_CLUSTER;
            writeAttributeRequest.attributeId = Constants.LOCATION_DESCRIPTION;
            writeAttributeRequest.args = actualLocation;

            domusEngine.writeAttribute(writeAttributeRequest);
        }
        if (request != null) {
            request.stop();
        }
        super.onPause();
    }

    @Override
    @UiThread
    public void newAttributes(List<JSonAttribute> attributes) {
        for (JSonAttribute attribute : attributes) {
            if (attribute.isSupported && attribute.isAvailable) {
                switch (attribute.id) {
                    case Constants.MANUFACTURER_NAME:
                        name.setText(attribute.value);
                        break;
                    case Constants.MODEL_IDENTIFIER:
                        model.setText(attribute.value);
                        break;
                    case Constants.DATE_CODE:
                        date.setText(attribute.value);
                        break;
                    case Constants.LOCATION_DESCRIPTION:
                        location.setText(attribute.value);
                        prevLocation = attribute.value;
                        break;
                    case Constants.PHYSICAL_ENVIRONMENT:
                        environment.setText(attribute.value);
                        break;
                    case Constants.DEVICE_ENABLED:
                        checkBox.setChecked(attribute.value.equals("1"));
                        break;
                }
            }
        }
    }
}
