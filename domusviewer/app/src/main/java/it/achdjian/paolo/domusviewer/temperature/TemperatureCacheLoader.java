package it.achdjian.paolo.domusviewer.temperature;

import com.google.common.base.Optional;
import com.google.common.cache.CacheLoader;

import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;

/**
 * Created by Paolo Achdjian on 02/09/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class TemperatureCacheLoader extends CacheLoader<String, Optional<Integer> > implements DomusEngine.AttributesListener {
    @Bean
    DomusEngine domusEngine;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    Map<String, Integer> values = new HashMap<>();

    public Optional<Integer> load(String roomName) throws Exception {
        Element element = tempSensorLocationDS.getElement(roomName);
        if (element != null) {
            domusEngine.requestAttributes(this, element.network, element.endpoint, Constants.ZCL_HA_DEVICEID_TEMPERATURE_SENSOR, new Integer(0));
            if (!values.containsKey(roomName)) {
               return Optional.absent();
            }
            return Optional.of(values.get(roomName));
        } else {
            return Optional.absent();
        }

    }

    @Override
    public void newAttributes(int networkId, int endpointId, List<JSonAttribute> attributes) {
        for (final JSonAttribute attribute : attributes) {
            if (attribute.isSupported && attribute.isAvailable && attribute.id == 0) {
                String room = tempSensorLocationDS.getRoom(networkId, endpointId);
                Integer value = Integer.valueOf(attribute.value);
                if (value != null) {
                    values.put(room, value);
                }
            }
        }
    }
}
