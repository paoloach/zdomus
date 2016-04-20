package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.support.annotation.NonNull;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

import it.achdjian.paolo.domusviewer.zigbee.ZEndpoint;

/**
 * Created by Paolo Achdjian on 18/04/16.
 */
public class GetEndpoint  extends DomusEngineRest {
    public interface Listener {
        void newEndpoint(ZEndpoint zEndpoint);
    }

    private final static ObjectMapper mapper = new ObjectMapper();
    private final Listener listener;
    private final int nwkAddress;
    private final int endpointId;

    public GetEndpoint(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, int nwkAddress, int endpointId, @NonNull Listener listener) {
        super(sharedPreferences, connected);
        this.nwkAddress = nwkAddress;
        this.endpointId = endpointId;
        this.listener = listener;
    }

    @Override
    public void run() {
        String body = get("/devices/"+nwkAddress+"/endpoint/" + endpointId);
        if (body != null) {
            if (!body.isEmpty()) {
                try {
                    ZEndpoint zEndpoint = mapper.readValue(body, ZEndpoint.class);
                    listener.newEndpoint(zEndpoint);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
