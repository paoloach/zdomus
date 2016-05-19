package it.achdjian.paolo.domusviewer.on_off;

import android.support.annotation.NonNull;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;

import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.zigbee.ClustersId;
import it.achdjian.paolo.domusviewer.zigbee.ZDevice;
import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 07/05/16.
 */
@EBean
class ElementSelected {
    @Bean
    DomusEngine domusEngine;

    public Element selected;

    boolean isSwitch() {
        if (selected != null) {
            ZDevice device = domusEngine.getDevices().getDevice(selected.network);
            if (device != null) {
                ZEndpoint endpoint = device.getEndpoin(selected.endpoint);
                if (endpoint.containsOutCluster(ClustersId.ON_OFF_CLUSTER)) {
                    return true;
                }
            }
        }
        return false;
    }

    boolean isLight() {
        if (selected != null) {
            ZDevice device = domusEngine.getDevices().getDevice(selected.network);
            if (device != null) {
                ZEndpoint endpoint = device.getEndpoin(selected.endpoint);
                if (endpoint.containsInCluster(ClustersId.ON_OFF_CLUSTER)) {
                    return true;
                }
            }
        }
        return false;
    }

    public boolean is(@NonNull Element element) {
        return element.equals(selected);
    }
}
