package it.achdjian.paolo.domusviewer.on_off;

import android.content.Context;
import android.os.Looper;
import android.view.LayoutInflater;

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
class LightAdapter extends OnOffAdapter {
    public LightAdapter( Context context, LayoutInflater inflater) {
        super( context, inflater);
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
}
