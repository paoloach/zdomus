package it.achdjian.paolo.domusviewer.other;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.DialogFragment;
import android.view.Window;
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
import it.achdjian.paolo.domusviewer.DomusEngineRest.DeviceInformation;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.DomusEngineRest.Stoppable;
import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 11/05/16.
 */
@EFragment(R.layout.zdevice_info)
public class ZDeviceInfoFragment extends DialogFragment implements DomusEngine.AttributesListener, DomusEngine.DeviceInformationListener {
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
    @ViewById(R.id.quality)
    TextView quality;
    @ViewById(R.id.tx_quality)
    TextView txQuality;
    @ViewById(R.id.enabled)
    CheckBox checkBox;
    @Bean
    DomusEngine domusEngine;
    private Stoppable requestAttr;
    private Stoppable requestQuality;
    private String prevLocation;

    @AfterViews
    public void afterView() {

        getDialog().setTitle("device " + networkId + " endpoint " + endpointId);
        prevLocation = "";
        name.setText("");
        model.setText("");
        date.setText("");
        location.setText("");
        environment.setText("");
        checkBox.setChecked(false);

        quality.setText(R.string.not_available);
        txQuality.setText(R.string.not_available);

        requestAttr = domusEngine.requestAttributes(this, networkId, endpointId, Constants.BASIC_CLUSTER,
                Constants.MANUFACTURER_NAME,
                Constants.MODEL_IDENTIFIER,
                Constants.DATE_CODE,
                Constants.LOCATION_DESCRIPTION,
                Constants.PHYSICAL_ENVIRONMENT,
                Constants.DEVICE_ENABLED);
        requestQuality = domusEngine.requestQuality(networkId, this);
    }

    @Override
    public void onResume() {
        super.onResume();
        int width = getResources().getDimensionPixelSize(R.dimen.info_device_width);
        int height = getResources().getDimensionPixelSize(R.dimen.info_device_height);
        Window window = getDialog().getWindow();
        if (window != null) {
            window.setLayout(width, height);
        }

    }

    @Override
    public void onPause() {
        String actualLocation = location.getText().toString();
        if (!actualLocation.equals(prevLocation)) {
            WriteAttributeRequest writeAttributeRequest = new WriteAttributeRequest();
            writeAttributeRequest.networkId = networkId;
            writeAttributeRequest.endpointId = endpointId;
            writeAttributeRequest.clusterId = Constants.BASIC_CLUSTER;
            writeAttributeRequest.attributeId = Constants.LOCATION_DESCRIPTION;
            writeAttributeRequest.args = actualLocation;

            domusEngine.writeAttribute(writeAttributeRequest);
        }
        if (requestAttr != null) {
            requestAttr.stop();
        }
        if (requestQuality != null) {
            requestQuality.stop();
        }
        super.onPause();
    }

    @Override
    @UiThread
    public void newAttributes(int networkId, int endpointId, List<JSonAttribute> attributes) {
        for (JSonAttribute attribute : attributes) {
            if (attribute.isSupported && attribute.isAvailable) {
                switch (attribute.id) {
                    case Constants.MANUFACTURER_NAME:
                        name.setText(attribute.value.trim());
                        break;
                    case Constants.MODEL_IDENTIFIER:
                        model.setText(attribute.value.trim());
                        break;
                    case Constants.DATE_CODE:
                        date.setText(attribute.value.trim());
                        break;
                    case Constants.LOCATION_DESCRIPTION:
                        location.setText(attribute.value.trim());
                        prevLocation = attribute.value;
                        break;
                    case Constants.PHYSICAL_ENVIRONMENT:
                        environment.setText(attribute.value.trim());
                        break;
                    case Constants.DEVICE_ENABLED:
                        checkBox.setChecked(attribute.value.equals("1"));
                        break;
                }
            }
        }
    }

    @Override
    @UiThread
    public void newDeviceInformation(@Nullable DeviceInformation information) {
        if (information != null) {
            quality.setText(Integer.toString(information.rxLqi));
            txQuality.setText(Integer.toString(information.txCost));
        } else {
            quality.setText(R.string.not_available);
            txQuality.setText(R.string.not_available);
        }

        requestQuality = domusEngine.requestQuality(networkId, this, 5000);
    }
}
