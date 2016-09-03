package it.achdjian.paolo.domusviewer.on_off;

import android.database.DataSetObserver;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListAdapter;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.utils.ElementView;
import it.achdjian.paolo.domusviewer.utils.ElementViewFactory;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
@EBean
abstract class OnOffAdapter implements ListAdapter, DomusEngine.EndpointListener {
    static final Integer TYPE_SWITCH = 1;
    static final Integer TYPE_LIGHT = 2;

    @RootContext
    AppCompatActivity activity;
    @Bean
    DomusEngine domusEngine;
    @Bean
    ElementViewFactory elementViewFactory;
    private int layout;

    BindController bindController;
    private final List<DataSetObserver> observers = new ArrayList<>();
    final List<Element> elements = new ArrayList<>();

    void init(@NonNull BindController bindController, int layout) {
        this.layout = layout;
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

    public ElementView getElementView(int position, View oldView, ViewGroup parent) {
        Element element = elements.get(position);
        ElementView elementView = elementViewFactory.createElementView(parent,layout, element, oldView);

        bindController.setBindStatus(elementView.view);
        elementView.selected(bindController.elementSelected.is(element));
        return elementView;
    }

    public void invalidate() {
        for (DataSetObserver observer : observers) {
            observer.onChanged();
        }
    }
}
