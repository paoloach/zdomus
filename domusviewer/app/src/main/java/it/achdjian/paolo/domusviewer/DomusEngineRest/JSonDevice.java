package it.achdjian.paolo.domusviewer.DomusEngineRest;

import com.fasterxml.jackson.annotation.JsonIgnore;

import java.util.HashMap;
import java.util.Map;

import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 18/04/16.
 */
public class JSonDevice {
    public int short_address;
    public String extended_address;
    public int capability;
    public Map<Integer,String> endpoints = new HashMap<>();
}
