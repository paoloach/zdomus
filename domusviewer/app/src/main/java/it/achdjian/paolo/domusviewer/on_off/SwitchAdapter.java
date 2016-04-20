package it.achdjian.paolo.domusviewer.on_off;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

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
class SwitchAdapter extends OnOffAdapter {
    public SwitchAdapter(Context context, LayoutInflater inflater) {
        super(context, inflater);
    }

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
        if (mainText != null)
            mainText.setText(element.network + ":" + element.endpoint);
        Button IButton = (Button) result.findViewById(R.id.identifyBt);
        if (IButton != null) {
            IButton.setTag(element);
            IButton.setOnClickListener(identifyListener);
        }
        return result;
    }
}
