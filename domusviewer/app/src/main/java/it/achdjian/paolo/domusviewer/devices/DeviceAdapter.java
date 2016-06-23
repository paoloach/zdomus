package it.achdjian.paolo.domusviewer.devices;

import android.database.DataSetObserver;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.RelativeLayout;
import android.widget.TextView;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.other.IdentifyListener;
import it.achdjian.paolo.domusviewer.other.ZDeviceInfoClick;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 21/06/16.
 */
@EBean
public class DeviceAdapter implements ListAdapter, DomusEngine.EndpointListener {
    @RootContext
    AppCompatActivity activity;
    @Bean
    DomusEngine domusEngine;
    @Bean
    ZDeviceInfoClick zDeviceInfoClick;
    @Bean
    IdentifyListener identifyListener;

    private final List<DataSetObserver> observers = new ArrayList<>();
    final List<Element> elements = new ArrayList<>();

    void init() {
        domusEngine.addEndpointListener(this);

        for (ZDevice zDevice : domusEngine.getDevices().getDevices()) {
            for (ZEndpoint zEndpoint : zDevice.getEndpoins()) {
                addEndpoint(zEndpoint);
            }
        }
    }

    @Override
    public boolean areAllItemsEnabled() {
        return false;
    }

    @Override
    public boolean isEnabled(int position) {
        return false;
    }

    @Override
    public void registerDataSetObserver(DataSetObserver observer) {
        observers.add(observer);
    }

    @Override
    public void unregisterDataSetObserver(DataSetObserver observer) {
        observers.remove(observer);
    }

    @Override
    public int getCount() {
        return elements.size();
    }

    @Override
    public Object getItem(int position) {
        return elements.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public boolean hasStableIds() {
        return true;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View result;
        if (convertView != null) {
            result = convertView;
        } else {
            LayoutInflater inflater = LayoutInflater.from(activity);
            result = inflater.inflate(R.layout.device_layout, parent, false);
        }
        Element element = elements.get(position);
        TextView mainText = (TextView) result.findViewById(R.id.mainText);
        String text = element.network + ":" + element.endpoint;
        mainText.setText(text);

        RelativeLayout infoLayout = (RelativeLayout) result.findViewById(R.id.deviceInfo);
        infoLayout.setLongClickable(false);
        infoLayout.setOnLongClickListener(zDeviceInfoClick);
        infoLayout.setTag(R.id.element_value, element);
        result.setTag(R.id.element_value, element);
        Button IButton = (Button) result.findViewById(R.id.identifyBt);
        IButton.setTag(element);
        IButton.setOnClickListener(identifyListener);

        return result;
    }

    @Override
    public int getItemViewType(int position) {
        return 1;
    }

    @Override
    public int getViewTypeCount() {
        return 1;
    }

    @Override
    public boolean isEmpty() {
        return elements.isEmpty();
    }

    @Override
    public void newEndpoint(ZEndpoint zDevice) {
        if (addEndpoint(zDevice)) {
            new Handler(activity.getMainLooper()).post(new Runnable() {
                @Override
                public void run() {
                    for (DataSetObserver observer : observers) {
                        observer.onChanged();
                    }
                }
            });
        }
    }


    private boolean addEndpoint(ZEndpoint zEndpoint) {
        Element newElement = new Element(zEndpoint.short_address, zEndpoint.endpoint_id);
        if (elements.indexOf(newElement) < 0) {
            elements.add(newElement);
            return true;
        }
        return false;
    }
}
