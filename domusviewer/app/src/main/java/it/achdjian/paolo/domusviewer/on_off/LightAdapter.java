package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.content.Context;
import android.support.annotation.NonNull;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_DIMMABLE_LIGHT;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_ON_OFF_LIGHT;
import static it.achdjian.paolo.domusviewer.Constants.ZCL_HA_DEVICEID_ON_OFF_OUTPUT;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
class LightAdapter extends OnOffAdapter implements View.OnClickListener {
    private final List<OnOffListener> listeners = new ArrayList<>();
    private final BindLightLongClickListener bindLightLongClickListener;

    public LightAdapter(Context context, @NonNull BindController bindController, @NonNull Binding binding, @NonNull ElementSelected selected, FragmentManager fragmentManager) {
        super(context, bindController, selected, fragmentManager);
        this.bindLightLongClickListener = new BindLightLongClickListener(selected, binding);
    }

    @Override
    boolean rightDevice(ZEndpoint zEndpoint) {
        return zEndpoint.device_id == ZCL_HA_DEVICEID_ON_OFF_OUTPUT ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_ON_OFF_LIGHT ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_DIMMABLE_LIGHT ||
                zEndpoint.device_id == ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT;
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
                    case ZCL_HA_DEVICEID_ON_OFF_OUTPUT:
                        return 0;
                    case ZCL_HA_DEVICEID_LEVEL_CONTROLLABLE_OUTPUT:
                        return 1;
                    case ZCL_HA_DEVICEID_ON_OFF_LIGHT:
                        return 2;
                    case ZCL_HA_DEVICEID_DIMMABLE_LIGHT:
                        return 3;
                    case ZCL_HA_DEVICEID_COLORED_DIMMABLE_LIGHT:
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
        result.setTag(R.id.type, TYPE_LIGHT);

        ImageView bind = (ImageView)result.findViewById(R.id.binded);
        bind.setTag(R.id.element_value,elements.get(position));
        bind.setOnLongClickListener(bindLightLongClickListener);
        return result;
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag(R.id.element_value);
        if (tag instanceof Element) {
            if (selected.is((Element) tag)) {
                selected.selected=null;
            } else {
                selected.selected= (Element) tag;
            }
            for (OnOffListener lightListener : listeners) {
                lightListener.change();
            }
        }
    }

    public void addListener(OnOffListener listener) {
        listeners.add(listener);
    }
}
