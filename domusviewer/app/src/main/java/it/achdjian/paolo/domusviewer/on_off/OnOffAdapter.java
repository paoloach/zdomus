package it.achdjian.paolo.domusviewer.on_off;

import android.annotation.SuppressLint;
import android.content.Context;
import android.database.DataSetObserver;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 20/04/16.
 */
abstract class OnOffAdapter implements ListAdapter, DomusEngine.EndpointListener {

    static final Integer TYPE_SWITCH =1;
    static final Integer TYPE_LIGHT =2;

    final DomusEngine domusEngine;
    private final IdentifyListener identifyListener;
    private final BindController bindController;
    final ElementSelected selected;

    private final List<DataSetObserver> observers = new ArrayList<>();
    final List<Element> elements = new ArrayList<>();
    private final Context context;

    OnOffAdapter(Context context,@NonNull BindController bindController,  ElementSelected selected) {
        this.context = context;
        this.bindController = bindController;
        this.selected = selected;
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
        RelativeLayout infoLayout = (RelativeLayout) result.findViewById(R.id.info_layout);
        mainText.setText(element.network + ":" + element.endpoint);

        result.setTag(R.id.element_value,element);
        Button IButton = (Button) result.findViewById(R.id.identifyBt);
        IButton.setTag(element);
        IButton.setOnClickListener(identifyListener);

        bindController.setBindStatus(result);
        if (selected.is(element)){
            infoLayout.setActivated(true);
        } else{
            infoLayout.setActivated(false);
        }
        return result;
    }

    public void invalidate(){
        for (DataSetObserver observer : observers) {
            observer.onChanged();
        }
    }
}
