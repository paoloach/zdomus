package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.text.TextUtils;
import android.util.Log;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.util.List;

import it.achdjian.paolo.domusviewer.DomusEngine;

/**
 * Created by Paolo Achdjian on 18/05/16.
 */
public class RequestAttributes extends DomusEngineRest implements Stoppable {
    private DomusEngine.AttributesListener listener;
    private final Integer networkId;
    private final Integer endpointId;
    private final int clusterId;
    private final Integer[] attributes;
    private boolean toStop;

    public RequestAttributes(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, @NonNull DomusEngine.AttributesListener listener, @NonNull Integer networkId, @NonNull Integer endpointId, int clusterId, @NonNull Integer[] attributes) {
        super(sharedPreferences, connected);
        this.listener = listener;
        this.networkId = networkId;
        this.endpointId = endpointId;
        this.clusterId = clusterId;
        this.attributes = attributes;
        toStop = false;
    }

    @Override
    public void run() {
        StringBuilder builder = new StringBuilder("/devices/").
                append(networkId).
                append("/endpoint/").
                append(endpointId).
                append("/cluster/in/").
                append(clusterId).
                append("/attributes?id=").append(TextUtils.join(",", attributes));
        String body = get(builder.toString());
        if (body != null && toStop==false) {
            if (!body.isEmpty()) {
                ObjectMapper mapper = new ObjectMapper();
                try {
                    List<JSonAttribute> attributes = mapper.readValue(body, new TypeReference<List<JSonAttribute>>() {
                    });
                    listener.newAttributes(attributes);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    @Override
    public void stop() {
        listener = null;
        toStop=true;
    }
}
