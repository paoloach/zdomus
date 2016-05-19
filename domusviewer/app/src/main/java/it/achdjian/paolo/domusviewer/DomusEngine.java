package it.achdjian.paolo.domusviewer;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Handler;
import android.os.HandlerThread;
import android.preference.PreferenceManager;
import android.support.annotation.NonNull;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.EBean;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import it.achdjian.paolo.domusviewer.DomusEngineRest.Bind;
import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionObserver;
import it.achdjian.paolo.domusviewer.DomusEngineRest.ConnectionStatus;
import it.achdjian.paolo.domusviewer.DomusEngineRest.GetDevices;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.DomusEngineRest.RequesetBindMap;
import it.achdjian.paolo.domusviewer.DomusEngineRest.RequestAttributes;
import it.achdjian.paolo.domusviewer.DomusEngineRest.RequestIdentify;
import it.achdjian.paolo.domusviewer.DomusEngineRest.Unbind;
import it.achdjian.paolo.domusviewer.DomusEngineRest.WhoAreYou;
import it.achdjian.paolo.domusviewer.zigbee.BindRequestData;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by paolo on 14/04/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class DomusEngine extends HandlerThread implements ConnectionObserver {
    private final Context context;
    public Map<Integer, Map<Element, Set<Element>>> srcDstBindMap = Collections.synchronizedMap(new HashMap<Integer, Map<Element, Set<Element>>>());
    public Map<Integer, Map<Element, Set<Element>>> dstSrcBindMap = Collections.synchronizedMap(new HashMap<Integer, Map<Element, Set<Element>>>());


    public interface EndpointListener {
        void newEndpoint(ZEndpoint zDevice);
    }

    public interface AttributesListener {
        void newAttributes(List<JSonAttribute> attributes);
    }

    private final ConnectionStatus connected = new ConnectionStatus();
    private SharedPreferences sharedPreferences;
    private ZDevices devices;

    public DomusEngine(Context context) {
        super("DomusEngine");
        this.context = context;
    }

    @AfterInject
    void init() {
        sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
        connected.addObserver(this);
        start();
        Handler handler = new Handler(getLooper());
        devices = new ZDevices(sharedPreferences, connected, getLooper());
        handler.post(new WhoAreYou(sharedPreferences, connected));
    }

    public void addConnectionObserver(@NonNull ConnectionObserver observer) {
        connected.addObserver(observer);
    }

    public void removeConnectionObserver(@NonNull ConnectionObserver observer) {
        connected.removeObserver(observer);
    }

    public void addEndpointListener(@NonNull EndpointListener listener) {
        devices.addListener(listener);
    }

    public void removeEndpointListener(@NonNull EndpointListener listener) {
        devices.deleteListener(listener);
    }


    public void requestIdentify(int network, int endpoint) {
        Handler handler = new Handler(getLooper());
        handler.post(new RequestIdentify(sharedPreferences, connected, network, endpoint));
    }

    public void requestBindMap() {
        Handler handler = new Handler(getLooper());
        handler.post(new RequesetBindMap(sharedPreferences, connected, srcDstBindMap, dstSrcBindMap));
    }

    public void bind(@NonNull BindRequestData data) {
        Handler handler = new Handler(getLooper());
        handler.post(new Bind(sharedPreferences, connected, data));
    }

    public void unbind(@NonNull BindRequestData data) {
        Handler handler = new Handler(getLooper());
        handler.post(new Unbind(sharedPreferences, connected, data));
    }

    public void requestAttributes(@NonNull AttributesListener listener, @NonNull Integer networkId, @NonNull Integer endpointId, int clusterId, Integer... attributes) {
        Handler handler = new Handler(getLooper());
        handler.post(new RequestAttributes(sharedPreferences, connected, listener, networkId, endpointId, clusterId, attributes));
    }

    @Override
    public void connected() {
        Handler handler = new Handler(getLooper());
        handler.post(new GetDevices(sharedPreferences, connected, devices));
    }

    @Override
    public void disconnected() {

    }

    @Override
    public boolean quit() {
        connected.removeObserver(this);
        devices.deleteAllListener();
        return super.quit();
    }

    public ZDevices getDevices() {
        return devices;
    }

    public List<Element> getBindedDest(int cluster, Element src) {
        return null;
    }
}
