package it.achdjian.paolo.domusviewer.database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.annotation.Nullable;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;

/**
 * Created by Paolo Achdjian on 31/08/16.
 */
@EBean(scope= EBean.Scope.Singleton)
public class TempSensorLocationDS {
    @RootContext
    Context context;
    @Bean
    DomusEngine domusEngine;

    public void createTempSensorLocation(String networkAddress, int endpoint, String location) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(context);
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
    }

    public void createTempSensorLocation(Element element, String location) {
        int network = element.network;
        ZDevices devices = domusEngine.getDevices();
        ZDevice device = devices.getDevice(network);
        createTempSensorLocation(device.extended_address, element.endpoint, location);
    }

    public boolean isLocationUsedYet(String location) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(context);
        SQLiteDatabase database = domusViewDatabase.getReadableDatabase();
        Cursor query = database.query(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE,
                new String[]{DomusViewDatabase.NETWORK_FIELD, DomusViewDatabase.ENDPOINT},
                DomusViewDatabase.LOCATION + "= ?",
                new String[]{location},
                null,
                null,
                null);
        if (query.getCount() <= 0) {
            return false;
        }
        return true;
    }

    public Element getElement(String roomName) {
        DomusViewDatabase domusViewDatabase = new DomusViewDatabase(context);
        SQLiteDatabase database = domusViewDatabase.getReadableDatabase();
        Cursor query = database.query(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE,
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
            return new Element(0,0);
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
            DomusViewDatabase domusViewDatabase = new DomusViewDatabase(context);
            SQLiteDatabase database=null;
            try {
                database = domusViewDatabase.getReadableDatabase();
                Cursor query = database.rawQuery(sqlQuery.toString(),null);
                if (query.getCount() <= 0) {
                    return null;
                }
                query.moveToFirst();
                return query.getString(0);
            } finally {
                if (database != null) {
                    database.close();
                }
            }

        } else {
            return null;
        }

    }
}
