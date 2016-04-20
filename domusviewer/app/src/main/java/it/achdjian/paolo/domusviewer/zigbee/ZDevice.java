package it.achdjian.paolo.domusviewer.zigbee;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonDevice;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class ZDevice {
    public int short_address;
    public String extended_address;
    public int capability;
    public Set<Integer> requestingEndpoint = new HashSet<>();
    public Map<Integer,ZEndpoint> endpoints = new HashMap<>();

    public ZDevice(JSonDevice json) {
        short_address = json.short_address;
        extended_address = json.extended_address;
        requestingEndpoint.addAll(json.endpoints.values());
        capability = json.capability;
    }

    public ZDevice(){
    }

    boolean hasEndpoint(Integer endpoint){
        for (Integer containedEndpoint  : endpoints.keySet()) {
            if (containedEndpoint.equals(endpoint)){
                return true;
            }
        }
        return false;
    }

    public void merge(JSonDevice zDevice) {
        requestingEndpoint.addAll(zDevice.endpoints.values());
    }

    public Collection<ZEndpoint> getEndpoins(){
        return endpoints.values();
    }

    public ZEndpoint getEndpoin(int endpoint) {
        return endpoints.get(endpoint);
    }
}
