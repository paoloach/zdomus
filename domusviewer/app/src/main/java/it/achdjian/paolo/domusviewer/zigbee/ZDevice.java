package it.achdjian.paolo.domusviewer.zigbee;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class ZDevice {
    public int short_address;
    public String extended_address;
    public int capability;
    public Map<Integer,Integer> endpoints= new HashMap<>();
}
