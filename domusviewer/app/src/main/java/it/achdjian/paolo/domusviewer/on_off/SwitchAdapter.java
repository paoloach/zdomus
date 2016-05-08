package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.content.Context;
import android.support.annotation.NonNull;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
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
class SwitchAdapter extends OnOffAdapter implements View.OnClickListener {
    private final List<OnOffListener> switchListeners = new ArrayList<>();
    private final BindSwitchLongClickListener bindSwitchLongClickListener;
    public SwitchAdapter(Context context, @NonNull BindController bindController, @NonNull Binding binding, @NonNull ElementSelected selected) {
        super(context, bindController, selected);
        this.bindSwitchLongClickListener = new BindSwitchLongClickListener(selected, binding);

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
    public View getView(int position, View convertView, ViewGroup parent) {
        View result = super.getView(position, convertView, parent);
        result.setOnClickListener(this);
        result.setTag(R.id.type, TYPE_SWITCH);

        ImageView bind = (ImageView)result.findViewById(R.id.binded);
        bind.setLongClickable(true);
        bind.setTag(R.id.element_value,elements.get(position));
        bind.setOnLongClickListener(bindSwitchLongClickListener);
        return result;
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag(R.id.element_value);
        if (tag instanceof Element) {
            if (selected.is((Element) tag)){
                selected.selected = null;
            } else {
                selected.selected= (Element) tag;
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
