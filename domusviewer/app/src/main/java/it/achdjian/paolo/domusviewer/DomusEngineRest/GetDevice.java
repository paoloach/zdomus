package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.os.Handler;
import android.support.annotation.NonNull;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

import it.achdjian.paolo.domusviewer.zigbee.ZDevice;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class GetDevice  extends DomusEngineRest  {
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
        String body = get("/devices/"+nwkAddress);
        if (body != null) {
            if (!body.isEmpty()) {
                ObjectMapper mapper = new ObjectMapper();
                try {
                    JSonDevice zDevice = mapper.readValue(body, JSonDevice.class);
                    listener.newDevice(zDevice);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
