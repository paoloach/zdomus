package it.achdjian.paolo.domusviewer.on_off;

import android.content.Context;
import android.database.DataSetObserver;
import android.os.Handler;
import android.view.LayoutInflater;
import android.widget.ListAdapter;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
abstract class OnOffAdapter implements ListAdapter, DomusEngine.EndpointListener {

    protected final DomusEngine domusEngine;
    protected final IdentifyListener identifyListener;

    static class Element {
        public final int network;
        public final int endpoint;

        public Element(int short_address, int endpoint_id) {
            network = short_address;
            endpoint = endpoint_id;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            Element element = (Element) o;

            return network == element.network && endpoint == element.endpoint;

        }

        @Override
        public int hashCode() {
            int result = network;
            result = 31 * result + endpoint;
            return result;
        }
    }

    private final List<DataSetObserver> observers = new ArrayList<>();
    protected final List<Element> elements = new ArrayList<>();
    protected final Context context;
    protected final LayoutInflater layoutInflater;

    OnOffAdapter( Context context, LayoutInflater layoutInflater) {
        this.context = context;
        this.layoutInflater = layoutInflater;
        domusEngine = DomusEngine.getInstance();
        domusEngine.addEndpointListener(this);

        for (ZDevice zDevice : domusEngine.getDevices().getDevices()) {
            for (ZEndpoint zEndpoint : zDevice.getEndpoins()) {
                addEndpoint(zEndpoint);
            }
        }
        identifyListener = new IdentifyListener();
    }

    public void onDestroy() {
        DomusEngine instance = DomusEngine.getInstance();
        instance.removeEndpointListener(this);
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
        if (addEndpoint(zDevice)){
            new Handler(context.getMainLooper()).post(new Runnable() {
                @Override
                public void run() {
                    for (DataSetObserver observer : observers) {
                        observer.onChanged();
                    }
                }
            });
        }
    }
}
