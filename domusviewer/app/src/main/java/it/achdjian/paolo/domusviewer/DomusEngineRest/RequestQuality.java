package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

import it.achdjian.paolo.domusviewer.DomusEngine;

/**
 * Created by Paolo Achdjian on 21/09/16.
 */

public class RequestQuality extends DomusEngineRest implements Stoppable {
    private final int networkId;
    private boolean toStop;
    private final DomusEngine.DeviceInformationListener listener;

    public RequestQuality(SharedPreferences sharedPreferences, ConnectionStatus connected, int networkId, DomusEngine.DeviceInformationListener listener) {
        super(sharedPreferences, connected);
        this.networkId = networkId;
        this.listener = listener;
        toStop = false;

    }

    @Override
    public void stop() {
        toStop = true;
    }

    @Override
    public void run() {
        String body = get("/devices/" + networkId + "/info");
        if (body != null && !toStop) {
            if (!body.isEmpty()) {
                ObjectMapper mapper = new ObjectMapper();
                try {
                    DeviceInformation information= mapper.readValue(body, DeviceInformation.class);
                    listener.newDeviceInformation(information);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            } else {
                listener.newDeviceInformation(null);
            }
        }
    }
}
