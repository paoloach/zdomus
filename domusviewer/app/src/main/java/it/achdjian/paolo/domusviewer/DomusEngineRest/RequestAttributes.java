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
public class    RequestAttributes extends DomusEngineRest implements Stoppable {
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
                append(Integer.toString(networkId,16)).
                append("/endpoint/").
                append(Integer.toString(endpointId,16)).
                append("/cluster/in/").
                append(Integer.toString(clusterId,16)).
                append("/attributes?id=").append(TextUtils.join(",", attributes));
        Log.d("REST",builder.toString());
        String body = getLongRead(builder.toString());
        if (body != null && toStop==false) {
            Log.d("REST respose", body);
            if (!body.isEmpty()) {
                ObjectMapper mapper = new ObjectMapper();
                try {
                    List<JSonAttribute> attributes = mapper.readValue(body, new TypeReference<List<JSonAttribute>>() {
                    });
                    listener.newAttributes(networkId, endpointId, attributes);
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
