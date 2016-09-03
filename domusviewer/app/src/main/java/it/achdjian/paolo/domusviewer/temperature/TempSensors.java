package it.achdjian.paolo.domusviewer.temperature;

import android.os.Handler;
import android.preference.PreferenceManager;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.WhoAreYou;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZDevices;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 30/08/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class TempSensors {
    @Bean
    DomusEngine domusEngine;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;


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
    }

    public int count() {
        return tempSensors.size();
    }

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

    public Collection<Element> getSelected(){
        return  selectedElements;
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
}
