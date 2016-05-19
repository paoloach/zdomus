package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.database.DataSetObserver;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.v4.app.DialogFragment;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
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
import it.achdjian.paolo.domusviewer.other.ZDeviceInfoFragment_;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
@EBean
abstract class OnOffAdapter implements ListAdapter, DomusEngine.EndpointListener, View.OnLongClickListener {
    static final Integer TYPE_SWITCH = 1;
    static final Integer TYPE_LIGHT = 2;

    @RootContext
    AppCompatActivity activity;
    @Bean
    DomusEngine domusEngine;
    @Bean
    IdentifyListener identifyListener;

    BindController bindController;
    private final List<DataSetObserver> observers = new ArrayList<>();
    final List<Element> elements = new ArrayList<>();

    void init(@NonNull BindController bindController) {
        this.bindController = bindController;
        domusEngine.addEndpointListener(this);

        for (ZDevice zDevice : domusEngine.getDevices().getDevices()) {
            for (ZEndpoint zEndpoint : zDevice.getEndpoins()) {
                addEndpoint(zEndpoint);
            }
        }
    }

    public void onDestroy() {
        domusEngine.removeEndpointListener(this);
    }

    private boolean addEndpoint(ZEndpoint zEndpoint) {
        if (rightDevice(zEndpoint)) {
            Element newElement = new Element(zEndpoint.short_address, zEndpoint.endpoint_id);
            if (elements.indexOf(newElement) < 0) {
                elements.add(newElement);
                return true;
            }
        }
        return false;
    }

    abstract boolean rightDevice(ZEndpoint zEndpoint);

    @Override
    public boolean areAllItemsEnabled() {
        return true;
    }

    @Override
    public boolean isEnabled(int position) {
        return true;
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
    public boolean isEmpty() {
        return false;
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

    @SuppressLint("SetTextI18n")
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View result;
        if (convertView != null) {
            result = convertView;
        } else {
            LayoutInflater inflater = LayoutInflater.from(activity);
            result = inflater.inflate(R.layout.switch_on_off, parent, false);
        }
        Element element = elements.get(position);
        TextView mainText = (TextView) result.findViewById(R.id.mainText);
        RelativeLayout infoLayout = (RelativeLayout) result.findViewById(R.id.info_layout);
        infoLayout.setLongClickable(false);
        infoLayout.setOnLongClickListener(this);
        infoLayout.setTag(R.id.element_value, element);


        mainText.setText(element.network + ":" + element.endpoint);

        result.setTag(R.id.element_value, element);
        Button IButton = (Button) result.findViewById(R.id.identifyBt);
        IButton.setTag(element);
        IButton.setOnClickListener(identifyListener);

        bindController.setBindStatus(result);
        if (bindController.elementSelected.is(element)) {
            infoLayout.setActivated(true);
        } else {
            infoLayout.setActivated(false);
        }
        return result;
    }

    public void invalidate() {
        for (DataSetObserver observer : observers) {
            observer.onChanged();
        }
    }

    @Override
    public boolean onLongClick(View v) {
        if (v instanceof RelativeLayout) {
            RelativeLayout infoLayout = (RelativeLayout) v;
            Object tag = infoLayout.getTag(R.id.element_value);
            if (tag instanceof Element) {
                FragmentManager fragmentManager = activity.getSupportFragmentManager();
                FragmentTransaction ft = fragmentManager.beginTransaction();
                Fragment prev = fragmentManager.findFragmentByTag("dialog");
                if (prev != null) {
                    ft.remove(prev);
                }
                ft.addToBackStack(null);

                // Create and show the dialog.
                Element element = (Element) tag;
                DialogFragment newFragment = ZDeviceInfoFragment_.builder().
                        endpointId(element.endpoint).
                        networkId(element.network).
                        build();
                newFragment.show(ft, "dialog");
                return true;
            }
        }
        return false;
    }
}
