package it.achdjian.paolo.domusviewer.temperature;

import android.app.Activity;
import android.database.DataSetObserver;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListAdapter;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import java.util.HashSet;
import java.util.Set;

import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.utils.ElementView;
import it.achdjian.paolo.domusviewer.utils.ElementViewFactory;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 30/08/16.
 */
@EBean
public class TemperatureSensorsAdapter implements ListAdapter, View.OnClickListener, EndpointObserver {
    private final Set<DataSetObserver> observerSet = new HashSet<>();
    @Bean
    TempSensors tempSensors;
    @Bean
    ElementViewFactory elementViewFactory;
    @RootContext
    Activity activity;

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
        observerSet.add(observer);
    }

    @Override
    public void unregisterDataSetObserver(DataSetObserver observer) {
        observerSet.remove(observer);
    }

    @Override
    public int getCount() {
        return tempSensors.count();
    }

    @Override
    public Object getItem(int position) {
        return tempSensors.get(position);
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
        ElementView elementView = elementViewFactory.createElementView(parent, R.layout.temp_sensor, tempSensors.get(position), convertView);
        elementView.infoLayout.setClickable(true);
        elementView.infoLayout.setOnClickListener(this);
        return elementView.view;
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag(R.id.element_view);
        if (tag instanceof ElementView) {
            ElementView elementView = (ElementView)tag;
            boolean isSelected = !elementView.isSelected();
            elementView.selected(isSelected);
            tempSensors.selected(elementView.element,isSelected);
        }
    }

    @Override
    public int getItemViewType(int position) {
        return 0;
    }

    @Override
    public int getViewTypeCount() {
        return 1;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public void newDevice(ZEndpoint endpoint) {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                for (DataSetObserver observer : observerSet) {
                    observer.onChanged();
                }
            }
        });
    }
}
