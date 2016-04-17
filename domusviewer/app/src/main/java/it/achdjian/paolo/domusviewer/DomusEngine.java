package it.achdjian.paolo.domusviewer;

import android.content.SharedPreferences;
import android.os.Handler;
import android.os.HandlerThread;

import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionObserver;
import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionStatus;
import it.achdjian.paolo.domusviewer.DomusEngineRest.GetDevices;
import it.achdjian.paolo.domusviewer.DomusEngineRest.WhoAreYou;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;

/**
 * Created by paolo on 14/04/16.
 */
public class DomusEngine  extends HandlerThread implements ConnectionObserver, ZDevices.Listener{
    private ConnectionStatus connected=new ConnectionStatus();
    private SharedPreferences sharedPreferences;
    private ZDevices devices;

    public void addConnectionObserver(ConnectionObserver observer){
        connected.addObserver(observer);
    }

    public void removeConnectionObserver(ConnectionObserver observer){
        connected.removeObserver(observer);
    }

    public DomusEngine(SharedPreferences sharedPreferences) {
        super("DomusEngine");
        connected.addObserver(this);
        this.sharedPreferences = sharedPreferences;
        start();
        Handler handler = new Handler(getLooper());
        devices = new ZDevices(sharedPreferences, connected, getLooper());
        handler.post(new WhoAreYou(sharedPreferences, connected));
        devices.addListener(this);
    }


    @Override
    public void connected() {
        Handler handler = new Handler(getLooper());
        handler.post(new GetDevices(sharedPreferences, connected,devices));
    }

    @Override
    public void disconnected() {

    }

    @Override
    public void newDevice(ZDevice zDevice) {

    }

    @Override
    public boolean quit(){
        connected.removeObserver(this);
        devices.deleteListener(this);
        return super.quit();
    }
}
