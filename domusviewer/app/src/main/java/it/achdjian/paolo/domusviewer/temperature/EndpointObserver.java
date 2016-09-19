package it.achdjian.paolo.domusviewer.temperature;

import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 10/09/16.
 */
public interface EndpointObserver {
    void newDevice(ZEndpoint endpoint);

}
