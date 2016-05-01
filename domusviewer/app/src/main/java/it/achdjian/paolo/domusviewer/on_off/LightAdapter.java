package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

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
class LightAdapter extends OnOffAdapter implements View.OnClickListener  {
    private final List<LightListener> lightListeners = new ArrayList<>();
    public LightAdapter(Context context) {
        super(context);
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
        View result;
        if (convertView != null) {
            result = convertView;
        } else {
            LayoutInflater inflater = LayoutInflater.from(context);
            result = inflater.inflate(R.layout.switch_on_off, parent, false);
        }
        Element element = elements.get(position);
        TextView mainText = (TextView) result.findViewById(R.id.mainText);
        mainText.setText(element.network + ":" + element.endpoint);
        result.setOnClickListener(this);
        result.setTag(element);
        Button IButton = (Button) result.findViewById(R.id.identifyBt);
        IButton.setTag(element);
        IButton.setOnClickListener(identifyListener);
        return result;
    }

    @Override
    public void onClick(View v) {
        boolean selected;

        selected = !v.isSelected();
        v.setSelected(selected);
        Object tag = v.getTag();
        if (tag instanceof Element) {
            for (LightListener lightListener : lightListeners) {
                lightListener.changeLight((Element) tag, selected);
            }
        }
    }

    public void  addListener(LightListener listener){
        lightListeners.add(listener);
    }
}
