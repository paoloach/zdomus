package it.achdjian.paolo.domusviewer;

import android.content.SharedPreferences;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.annotation.NonNull;

import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionObserver;
import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionStatus;
import it.achdjian.paolo.domusviewer.DomusEngineRest.GetDevices;
import it.achdjian.paolo.domusviewer.DomusEngineRest.RequestIdentify;
import it.achdjian.paolo.domusviewer.DomusEngineRest.WhoAreYou;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by paolo on 14/04/16.
 */
public class DomusEngine  extends HandlerThread implements ConnectionObserver{
    private static DomusEngine instance=null;


    public interface EndpointListener {
        void newEndpoint(ZEndpoint zDevice );
    }

    private final ConnectionStatus connected=new ConnectionStatus();
    private final SharedPreferences sharedPreferences;
    private final ZDevices devices;

    public static void initInstance(SharedPreferences sharedPreferences){
        instance = new DomusEngine(sharedPreferences);
    }


    private DomusEngine(SharedPreferences sharedPreferences) {
        super("DomusEngine");
        connected.addObserver(this);
        this.sharedPreferences = sharedPreferences;
        start();
        Handler handler = new Handler(getLooper());
        devices = new ZDevices(sharedPreferences, connected, getLooper());
        handler.post(new WhoAreYou(sharedPreferences, connected));
    }

    @NonNull
    public static DomusEngine getInstance() {
        return instance;
    }

    public void addConnectionObserver(ConnectionObserver observer){
        connected.addObserver(observer);
    }

    public void removeConnectionObserver(ConnectionObserver observer){
        connected.removeObserver(observer);
    }

    public void addEndpointListener(EndpointListener listener){
        devices.addListener(listener);
    }

    public void removeEndpointListener(EndpointListener listener){
        devices.deleteListener(listener);
    }


    public void requestIdentify(int network, int endpoint) {
        Handler handler = new Handler(getLooper());
        handler.post(new RequestIdentify(sharedPreferences, connected,network,endpoint));
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
    public boolean quit(){
        connected.removeObserver(this);
        devices.deleteAllListener();
        return super.quit();
    }

    public ZDevices getDevices() {
        return devices;
    }
}
