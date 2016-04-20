package it.achdjian.paolo.domusviewer.zigbee;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by Paolo Achdjian on 18/04/16.
 */
public class ZEndpoint {
    public int short_address;
    public int endpoint_id;
    public int profile_id;
    public int device_id;
    public int device_version;
    public Map<Integer, Integer> input_clusters = new HashMap<>();
    public Map<Integer, Integer> output_clusters = new HashMap<>();
}
