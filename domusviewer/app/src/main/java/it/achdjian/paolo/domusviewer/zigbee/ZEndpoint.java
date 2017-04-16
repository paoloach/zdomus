package it.achdjian.paolo.domusviewer.zigbee;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by Paolo Achdjian on 18/04/16.
 */
public class ZEndpoint {
    public String short_address;
    public String endpoint_id;
    public int profile_id;
    public int device_id;
    public int device_version;
    public Map<Integer, Integer> input_clusters = new HashMap<>();
    public Map<Integer, Integer> output_clusters = new HashMap<>();
    public boolean containsOutCluster(int cluster){
        for (Integer clusterID : output_clusters.values()) {
            if (clusterID == cluster){
                return true;
            }
        }
        return  false;
    }

    public boolean containsInCluster(int cluster){
        for (Integer clusterID : input_clusters.values()) {
            if (clusterID == cluster){
                return true;
            }
        }
        return  false;
    }

    public int getShortAddress() {
        return Integer.parseInt(short_address,16);
    }

    public int getEndpointId(){
        return Integer.parseInt(endpoint_id,16);
    }
}
