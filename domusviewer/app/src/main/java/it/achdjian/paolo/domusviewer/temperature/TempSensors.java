package it.achdjian.paolo.domusviewer.temperature;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;

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
public class TempSensors implements DomusEngine.EndpointListener {
    @Bean
    DomusEngine domusEngine;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    @Bean
    ActivityManager activityManager;


    private Set<EndpointObserver> endpointObserver = new HashSet<>();
    private List<Element> tempSensors = new ArrayList<>();
    private List<Element> unusedTempSensor = new ArrayList<>();
    private Set<Element> selectedElements = new HashSet<>();

    @AfterInject
    void init() {
        ZDevices zDevices = domusEngine.getDevices();
        for (ZDevice zDevice : zDevices.getDevices()) {
            for (ZEndpoint endpoint : zDevice.getEndpoins()) {
                if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR) {
                    Element newElement = new Element(endpoint.getShortAddress(), endpoint.getEndpointId());
                    tempSensors.add(newElement);
                }
            }
        }
        domusEngine.addEndpointListener(this);
    }

    @Nullable
    public Element get(int position) {
        return (position >= 0 && position < tempSensors.size()) ? tempSensors.get(position) : null;
    }

    @Nullable
    public Element getUnused(int position) {
        return (position >= 0 && position < unusedTempSensor.size()) ? unusedTempSensor.get(position) : null;
    }

    public void selected(@NonNull Element element, boolean selected) {
        if (selected) {
            selectedElements.add(element);
        } else {
            selectedElements.remove(element);
        }
    }

    @Nullable
    public Element getSelected() {
        if (selectedElements.isEmpty()) {
            return null;
        }
        return selectedElements.iterator().next();
    }

    public boolean someUnused() {
        return countUnused() > 0;
    }

    public void addObserver(@Nullable EndpointObserver observer) {
        if (observer != null) {
            endpointObserver.add(observer);
        }
    }

    public void removeObserver(@NonNull EndpointObserver endpointObserver) {
        this.endpointObserver.remove(endpointObserver);
    }

    @Override
    public void newEndpoint(final @NonNull ZEndpoint endpoint) {
        if (endpoint.device_id == Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR) {
            Element newElement = new Element(endpoint.getShortAddress(), endpoint.getEndpointId());
            tempSensors.add(newElement);
            activityManager.runOnActivityThread(new Runnable() {
                @Override
                public void run() {
                    for (it.achdjian.paolo.domusviewer.temperature.EndpointObserver endpointOvserver : endpointObserver) {
                        endpointOvserver.newDevice(endpoint);
                    }
                }
            });

        }
    }

    public int countUnused() {
        unusedTempSensor.clear();
        for (Element element: tempSensors){
            if (tempSensorLocationDS.getRoom(element.getNetwork(), element.getEndpoint())==null){
                unusedTempSensor.add(element);
            }
        }
        return unusedTempSensor.size();
    }

}
