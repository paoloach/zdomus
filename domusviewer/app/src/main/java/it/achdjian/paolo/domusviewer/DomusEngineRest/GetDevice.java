package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.support.annotation.NonNull;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class GetDevice  extends DomusEngineRest  {
    private static ObjectMapper MAPPER = new ObjectMapper();
    public interface Listener {
        void newDevice(JSonDevice zDevice);
    }

    private final int nwkAddress;
    @NonNull
    private final Listener listener;

    public GetDevice(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, int nwkAddress, @NonNull Listener listener) {
        super(sharedPreferences, connected);
        this.nwkAddress = nwkAddress;
        this.listener = listener;
    }

    @Override
    public void run() {
        String body = get("/devices/"+Integer.toString(nwkAddress,16));
        if (body != null) {
            if (!body.isEmpty()) {
                try {
                    JSonDevice zDevice = MAPPER.readValue(body, JSonDevice.class);
                    listener.newDevice(zDevice);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
