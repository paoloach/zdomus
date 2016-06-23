package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.support.annotation.NonNull;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;
import android.widget.ImageView;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.EBean;

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
@EBean
class LightAdapter extends OnOffAdapter implements View.OnClickListener {
    private ListLightController lightControllers;
    private final List<OnOffListener> listeners = new ArrayList<>();
    private BindLightLongClickListener bindLightLongClickListener;

    public void init(@NonNull BindController bindController, @NonNull Binding binding) {
        init(bindController, R.layout.light);
        this.bindLightLongClickListener = new BindLightLongClickListener(bindController.elementSelected, binding);
    }

    @AfterInject
    public void init(){
        lightControllers = new ListLightController(domusEngine);
    }


    public void onDestroy() {
        super.onDestroy();
        lightControllers.destroy();
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
        Element element = elements.get(position);
        result.setOnClickListener(this);
        result.setTag(R.id.type, TYPE_LIGHT);
        View infoLayout = result.findViewById(R.id.info_layout);
        infoLayout.setClickable(true);
        infoLayout.setOnClickListener(this);

        ImageButton light = (ImageButton)result.findViewById(R.id.lightBt);
        lightControllers.add(light, element);

        ImageView bind = (ImageView)result.findViewById(R.id.binded);
        bind.setTag(R.id.element_value,elements.get(position));
        bind.setOnLongClickListener(bindLightLongClickListener);
        return result;
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag(R.id.element_value);
        if (tag instanceof Element) {
            if (bindController.elementSelected.is((Element) tag)) {
                bindController.elementSelected.selected=null;
            } else {
                bindController.elementSelected.selected= (Element) tag;
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
