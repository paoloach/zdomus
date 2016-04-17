package it.achdjian.paolo.domusviewer.zigbee;

import android.content.SharedPreferences;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.NonNull;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionStatus;
import it.achdjian.paolo.domusviewer.DomusEngineRest.GetDevice;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class ZDevices implements GetDevice.Listener {
    public interface Listener {
        void newDevice(ZDevice zDevice );
    }

    private final SharedPreferences sharedPreferences;
    private final ConnectionStatus connected;
    private final Map<Integer, ZDevice> devices = new TreeMap<>();
    private final List<Listener> listeners = new ArrayList<>();
    private final Looper looper;

    public ZDevices(@NonNull SharedPreferences sharedPreferences,@NonNull ConnectionStatus connected,@NonNull Looper looper) {
        this.sharedPreferences = sharedPreferences;
        this.connected = connected;
        this.looper = looper;
    }


    public void addListener(@NonNull Listener listener){
        listeners.add(listener);
    }

    public void deleteListener(@NonNull  Listener listener){
        listeners.remove(listener);
    }

    public void addDevice(@NonNull  String shortAddress, @NonNull String extAddress){
        int nwkAddress;
        try {
            nwkAddress = Integer.parseInt(shortAddress);

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
    public void newDevice(@NonNull ZDevice zDevice) {
        devices.put(zDevice.short_address,zDevice);
    }
}
