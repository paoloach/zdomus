package it.achdjian.paolo.domusviewer.temperature;

import android.app.Activity;
import android.support.annotation.Nullable;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.other.ActivityManager;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 30/08/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class TempSensors implements  DomusEngine.EndpointListener{
    @Bean
    DomusEngine domusEngine;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    @Bean
    ActivityManager activityManager;


    private Set<EndpointObserver> EndpointObserver =new HashSet<>();
    private List<Element> tempSensors = new ArrayList<>();
    private Set<Element> selectedElements = new HashSet<>();

    @AfterInject
    void init() {
        ZDevices zDevices = domusEngine.getDevices();
        for(ZDevice zDevice: zDevices.getDevices()){
            for(ZEndpoint endpoint: zDevice.getEndpoins()){
                if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR){
                    Element newElement = new Element(endpoint.short_address, endpoint.endpoint_id);
                    tempSensors.add(newElement);
                }
            }
        }
        domusEngine.addEndpointListener(this);
    }

    public int count() {
        return tempSensors.size();
    }

    @Nullable
    public Element get(int position) {
        return (position >= 0 & position < tempSensors.size()) ? tempSensors.get(position) : null;
    }

    public void selected(Element element, boolean selected) {
        if (selected) {
            selectedElements.add(element);
        } else {
            selectedElements.remove(element);
        }
    }

    @Nullable
    public Element getSelected(){
        if (selectedElements.isEmpty()){
            return null;
        }
        return  selectedElements.iterator().next();
    }

    public boolean someUnused() {
        boolean unused=false;
        for(Element element: tempSensors){
            if (tempSensorLocationDS.getRoom(element.network,element.endpoint)==null){
                unused=true;
            }
        }
        return  unused;
    }

    public void addObserver(EndpointObserver observer){
        if (observer != null) {
            EndpointObserver.add(observer);
        }
    }

    public void removeObserver(EndpointObserver endpointObserver){
        EndpointObserver.remove(endpointObserver);
    }

    @Override
    public void newEndpoint(final ZEndpoint endpoint) {
        if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR){
            Element newElement = new Element(endpoint.short_address, endpoint.endpoint_id);
            tempSensors.add(newElement);
            activityManager.runOnActivityThread(new Runnable() {
                @Override
                public void run() {
                    for (it.achdjian.paolo.domusviewer.temperature.EndpointObserver endpointOvserver : EndpointObserver) {
                        endpointOvserver.newDevice(endpoint);
                    }
                }
            });

        }
    }
}
