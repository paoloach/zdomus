package it.achdjian.paolo.domusviewer.database;

import android.app.Application;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.DataSetObserver;
import android.database.sqlite.SQLiteDatabase;
import android.support.annotation.Nullable;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListAdapter;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import java.util.HashSet;
import java.util.Set;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.R;
import it.achdjian.paolo.domusviewer.temperature.EndpointObserver;
import it.achdjian.paolo.domusviewer.temperature.TempSensors;
import it.achdjian.paolo.domusviewer.utils.ElementView;
import it.achdjian.paolo.domusviewer.utils.ElementViewFactory;
import it.achdjian.paolo.domusviewer.utils.UiObservers;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 31/08/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class TempSensorLocationDS implements ListAdapter, View.OnClickListener, EndpointObserver {
    private UiObservers observers;
    @Bean
    DomusEngine domusEngine;
    @Bean
    TempSensors tempSensors;
    @Bean
    ElementViewFactory elementViewFactory;
    @RootContext
    Application application;

    public void createObservers() {
        observers = new UiObservers();
    }


    public void createTempSensorLocation(String networkAddress, int endpoint, String location) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(application);
        SQLiteDatabase database = domusViewDatabase.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put(DomusViewDatabase.NETWORK_FIELD, networkAddress);
        values.put(DomusViewDatabase.ENDPOINT, endpoint);
        values.put(DomusViewDatabase.LOCATION, location);
        database.beginTransaction();
        database.insert(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE, null, values);
        database.setTransactionSuccessful();
        database.endTransaction();
        database.close();
        observers.onChangeNotify();
    }

    public void removeTempSensorLocation(String location) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(application);
        SQLiteDatabase database = domusViewDatabase.getWritableDatabase();
        String[] values = {location};
        database.beginTransaction();
        database.delete(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE, DomusViewDatabase.LOCATION + "=?", values);
        database.setTransactionSuccessful();
        database.endTransaction();
        database.close();
        observers.onChangeNotify();
    }

    public void createTempSensorLocation(Element element, String location) {
        int network = element.getNetwork();
        ZDevices devices = domusEngine.getDevices();
        ZDevice device = devices.getDevice(network);
        if (device != null) {
            createTempSensorLocation(device.extended_address, element.getEndpoint(), location);
        }
        observers.onChangeNotify();
    }

    public boolean isLocationUsedYet(String location) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(application);
        SQLiteDatabase database = domusViewDatabase.getReadableDatabase();
        Cursor query = null;
        try {
            query = database.query(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE,
                    new String[]{DomusViewDatabase.NETWORK_FIELD, DomusViewDatabase.ENDPOINT},
                    DomusViewDatabase.LOCATION + "= ?",
                    new String[]{location},
                    null,
                    null,
                    null);
            return query.getCount() > 0;
        } finally {
            if (query != null) {
                query.close();
            }
        }
    }

    public Element getElement(String roomName) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(application);
        SQLiteDatabase database = domusViewDatabase.getReadableDatabase();
        Cursor query = null;
        try {
            query = database.query(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE,
                    new String[]{DomusViewDatabase.NETWORK_FIELD, DomusViewDatabase.ENDPOINT},
                    DomusViewDatabase.LOCATION + "= ?",
                    new String[]{roomName},
                    null,
                    null,
                    null);
            if (query.getCount() <= 0) {
                return null;
            }
            query.moveToFirst();

            String extAddress = query.getString(0);

            ZDevice device = domusEngine.getDevices().getDevice(extAddress);
            if (device != null) {
                return new Element(device.short_address, query.getInt(1));
            } else {
                return new Element(0, 0);
            }
        } finally {
            if (query != null) {
                query.close();
            }
        }
    }

    @Nullable
    public String getRoom(int networkId, int endpointId) {

        ZDevice device = domusEngine.getDevices().getDevice(networkId);
        if (device != null) {
            StringBuilder sqlQuery = new StringBuilder();
            sqlQuery.append("SELECT ").append(DomusViewDatabase.LOCATION).append(" from ").append(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE).
                    append(" WHERE ").append(DomusViewDatabase.NETWORK_FIELD).append("= '").append(device.extended_address).
                    append("' AND ").append(DomusViewDatabase.ENDPOINT).append(" = ").append(endpointId).append(";");
            DomusViewDatabase domusViewDatabase = new DomusViewDatabase(application);
            SQLiteDatabase database = null;
            Cursor query = null;
            try {
                database = domusViewDatabase.getReadableDatabase();
                query = database.rawQuery(sqlQuery.toString(), null);
                if (query.getCount() <= 0) {
                    return null;
                }
                query.moveToFirst();
                return query.getString(0);
            } finally {
                if (query != null) {
                    query.close();
                }
                if (database != null) {
                    database.close();
                }
            }

        } else {
            return null;
        }
    }

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
        return tempSensors.countUnused();
    }

    @Override
    public Object getItem(int position) {
        return tempSensors.getUnused(position);
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
        ElementView elementView = elementViewFactory.createElementView(parent, R.layout.temp_sensor, tempSensors.getUnused(position), convertView);
        elementView.infoLayout.setClickable(true);
        elementView.infoLayout.setOnClickListener(this);
        return elementView.view;
    }

    @Override
    public void onClick(View v) {
        Object tag = v.getTag(R.id.element_view);
        if (tag instanceof ElementView) {
            ElementView elementView = (ElementView) tag;
            boolean isSelected = !elementView.isSelected();
            elementView.selected(isSelected);
            tempSensors.selected(elementView.element, isSelected);
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
        return tempSensors.countUnused() == 0;
    }

    @Override
    public void newDevice(ZEndpoint endpoint) {
        observers.onChangeNotify();
    }

}
