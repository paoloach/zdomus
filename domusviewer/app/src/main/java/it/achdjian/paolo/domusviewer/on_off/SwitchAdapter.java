package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.support.annotation.NonNull;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import org.androidannotations.annotations.EBean;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.utils.ElementView;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_DIMMER_SWITCH;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_ON_OFF_SWITCH;

/**
 * Created by Paolo Achdjian on 19/04/16.
 */
@EBean
class SwitchAdapter extends OnOffAdapter implements View.OnClickListener {
    private final List<OnOffListener> switchListeners = new ArrayList<>();
    private BindSwitchLongClickListener bindSwitchLongClickListener;


    public void init(@NonNull BindController bindController, @NonNull Binding binding) {
        init(bindController, R.layout.switch_on_off);
        this.bindSwitchLongClickListener = new BindSwitchLongClickListener(bindController.elementSelected, binding);

    }

    @Override
    boolean rightDevice(ZEndpoint zEndpoint) {
        return zEndpoint.device_id == ZCL_HA_DEVICEID_ON_OFF_SWITCH ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_DIMMER_SWITCH ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH;
    }

    @Override
    public int getViewTypeCount() {
        return 5;
    }

    @Override
    public int getItemViewType(int position) {
        Element element = elements.get(position);
        ZDevice device = domusEngine.getDevices().getDevice(element.network);
        if (device != null) {
            ZEndpoint endpoint = device.getEndpoin(element.endpoint);
            if (endpoint != null) {
                switch (endpoint.device_id) {
                    case ZCL_HA_DEVICEID_ON_OFF_SWITCH:
                        return 0;
                    case ZCL_HA_DEVICEID_LEVEL_CONTROL_SWITCH:
                        return 1;
                    case ZCL_HA_DEVICEID_ON_OFF_LIGHT_SWITCH:
                        return 2;
                    case ZCL_HA_DEVICEID_DIMMER_SWITCH:
                        return 3;
                    case ZCL_HA_DEVICEID_COLOR_DIMMER_SWITCH:
                        return 4;
                }
            }
        }
        return 0;
    }


    @SuppressLint("SetTextI18n")
    @Override
    public View getView(int position, View oldView, ViewGroup parent) {
        ElementView elementView = getElementView(position, oldView, parent);
        elementView.setOnClickListener(this);
        elementView.setTagType(TYPE_SWITCH);
        elementView.infoLayout.setClickable(true);
        elementView.infoLayout.setOnClickListener(this);

        ImageView bind = (ImageView)elementView.view.findViewById(R.id.binded);
        bind.setTag(R.id.element_value,elements.get(position));
        bind.setOnLongClickListener(bindSwitchLongClickListener);
        return elementView.view;
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag(R.id.element_value);
        if (tag instanceof Element) {
            if (bindController.elementSelected.is((Element) tag)){
                bindController.elementSelected.selected = null;
            } else {
                bindController.elementSelected.selected= (Element) tag;
            }
            for (OnOffListener switchListener : switchListeners) {
                switchListener.change();
            }
        }
    }

    public void addListener(OnOffListener listener){
        switchListeners.add(listener);
    }
}
