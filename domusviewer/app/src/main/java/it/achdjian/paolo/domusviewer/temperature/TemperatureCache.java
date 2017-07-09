package it.achdjian.paolo.domusviewer.temperature;

import android.support.annotation.NonNull;
import android.util.Log;

import com.google.common.base.Optional;
import com.google.common.cache.CacheBuilder;
import com.google.common.cache.CacheLoader;
import com.google.common.cache.LoadingCache;

import org.androidannotations.annotations.AfterInject;
import org.androidannotations.annotations.Bean;
import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.Trace;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;

import it.achdjian.paolo.domusviewer.Constants;
import it.achdjian.paolo.domusviewer.DomusEngine;
import it.achdjian.paolo.domusviewer.DomusEngineRest.JSonAttribute;
import it.achdjian.paolo.domusviewer.Element;
import it.achdjian.paolo.domusviewer.database.TempSensorLocationDS;

/**
 * Created by Paolo Achdjian on 02/09/16.
 */
@EBean(scope = EBean.Scope.Singleton)
public class TemperatureCache extends CacheLoader<String, Optional<Integer>> implements DomusEngine.AttributesListener {
    @Bean
    DomusEngine domusEngine;
    @Bean
    TempSensorLocationDS tempSensorLocationDS;
    private TemperatureRender temperatureRender = null;
    private final Map<String, Integer> values = new HashMap<>();
    private LoadingCache<String, Optional<Integer>> cache;


    @AfterInject
    public void init() {
        cache = CacheBuilder.newBuilder()
                .expireAfterWrite(5, TimeUnit.MINUTES)
                .build(this);
    }
    @Trace(tag="REST")
    public Optional<Integer> getTemperature(@NonNull String roomName){
        return cache.getUnchecked(roomName);
    }


    @Override
    @Trace(tag="REST")
    public Optional<Integer> load(@NonNull String roomName) throws Exception {
        Element element = tempSensorLocationDS.getElement(roomName);
        if (element != null) {

            domusEngine.requestAttributes(this, element.getNetwork(), element.getEndpoint(), Constants.TEMPERATURE_MEASUREMENT, 0);
            if (!values.containsKey(roomName)) {
                return Optional.absent();
            }
            return Optional.of(values.get(roomName));
        } else {
            return Optional.absent();
        }
    }

    @Override
    @Trace(tag="REST")
    public void newAttributes(int networkId, int endpointId, List<JSonAttribute> attributes) {
        for (final JSonAttribute attribute : attributes) {
            if (attribute.isSupported && attribute.isAvailable && attribute.id == 0) {
                String room = tempSensorLocationDS.getRoom(networkId, endpointId);
                Integer value = Integer.valueOf(attribute.value);
                if (value != null) {
                    if (!values.containsKey(room)) {
                        values.put(room, value);
                        if (temperatureRender != null){
                            temperatureRender.notifyFirstTemperature(room);
                        }
                    } else {
                        values.put(room, value);
                    }
                }
            }
        }
    }

    public void setRender(TemperatureRender render) {
        this.temperatureRender = render;
    }

    public void invalidate(String room) {
        cache.invalidate(room);
    }
}
