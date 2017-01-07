package it.achdjian.paolo.domusviewer.zigbee;

import android.content.SharedPreferences;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionStatus;
import it.achdjian.paolo.domusviewer.DomusEngineRest.GetDevice;
import it.achdjian.paolo.domusviewer.DomusEngineRest.GetEndpoint;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonDevice;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class ZDevices implements GetDevice.Listener, GetEndpoint.Listener {
    private static final String TAG=ZDevices.class.getName();


    private final SharedPreferences sharedPreferences;
    private final ConnectionStatus connected;
    private final Map<Integer, ZDevice> devices = new TreeMap<>();
    private final List<DomusEngine.EndpointListener> listeners = new ArrayList<>();
    private final Looper looper;

    public ZDevices(@NonNull SharedPreferences sharedPreferences,@NonNull ConnectionStatus connected,@NonNull Looper looper) {
        this.sharedPreferences = sharedPreferences;
        this.connected = connected;
        this.looper = looper;
    }


    public void addListener(@NonNull DomusEngine.EndpointListener listener){
        listeners.add(listener);
    }

    public void deleteListener(@NonNull DomusEngine.EndpointListener listener){
        listeners.remove(listener);
    }

    public void addDevice(@NonNull  String shortAddress, @NonNull String extAddress){
        int nwkAddress;
        try {
            nwkAddress = Integer.parseInt(shortAddress,16);

            if (!devices.containsKey(nwkAddress)) {
                ZDevice zDevice = new ZDevice();
                zDevice.extended_address =extAddress;
                zDevice.short_address =nwkAddress;
                devices.put(nwkAddress, zDevice);
                Handler handler = new Handler(looper);
                handler.post(new GetDevice(sharedPreferences,connected,nwkAddress, this));
            }
        } catch (Exception ignored){

        }
    }

    @Override
    public void newDevice(@NonNull JSonDevice jSonDevice) {
        ZDevice existingDevice;
        if (!devices.containsKey(jSonDevice.short_address)) {
            existingDevice = devices.get(jSonDevice.short_address);
            existingDevice.merge(jSonDevice);
        } else {
            existingDevice = new ZDevice(jSonDevice);
            devices.put(jSonDevice.short_address,existingDevice);
        }
        if (!existingDevice.requestingEndpoint.isEmpty()) {
            Integer endpoint = existingDevice.requestingEndpoint.iterator().next();
            Handler handler = new Handler(looper);
            handler.post(new GetEndpoint(sharedPreferences,connected,jSonDevice.short_address, endpoint, this));
        }
    }

    @Override
    public void newEndpoint(ZEndpoint zEndpoint) {
        if (devices.containsKey(zEndpoint.short_address)){
            ZDevice existingDevice = devices.get(zEndpoint.short_address);
            for (DomusEngine.EndpointListener listener : listeners) {
                listener.newEndpoint(zEndpoint);
            }
            existingDevice.endpoints.put(zEndpoint.endpoint_id, zEndpoint);
            existingDevice.requestingEndpoint.remove(zEndpoint.endpoint_id);
            if (!existingDevice.requestingEndpoint.isEmpty()) {
                Integer endpoint = existingDevice.requestingEndpoint.iterator().next();
                Handler handler = new Handler(looper);
                handler.post(new GetEndpoint(sharedPreferences,connected,zEndpoint.short_address, endpoint, this));
            }
        } else {
            Log.e(TAG,"received an endpoint (" + zEndpoint.endpoint_id + ") description of a not previous declared device: " + zEndpoint.short_address);
        }
    }

    public void deleteAllListener() {
        listeners.clear();
    }

    @NonNull
    public Collection<ZDevice> getDevices(){
        return devices.values();
    }

    @Nullable
    public ZDevice getDevice(int networkId){
        return devices.get(networkId);
    }

    public boolean existDevice(int networkId){
        return devices.containsKey(networkId);
    }

    @Nullable
    public ZDevice getDevice(String extAddress){
        for(ZDevice device: devices.values()){
            if (device.extended_address.equals(extAddress)){
                return device;
            }
        }
        return null;
    }
}
