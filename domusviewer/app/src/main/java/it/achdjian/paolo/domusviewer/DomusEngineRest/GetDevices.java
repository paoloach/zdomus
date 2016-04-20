package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.util.Log;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.util.Map;

import it.achdjian.paolo.domusviewer.zigbee.ZDevices;

/**
 * Created by paolo on 15/04/16.
 */
public class GetDevices extends DomusEngineRest {
    private final ZDevices zDevices;

    public GetDevices(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, @NonNull ZDevices zDevices) {
        super(sharedPreferences, connected);
        this.zDevices = zDevices;
    }


    @Override
    public void run() {
        String body = get("/devices");
        if (body != null) {
            if (!body.isEmpty()) {
                ObjectMapper mapper = new ObjectMapper();
                try {
                    Map<String, String> devices = mapper.readValue(body, new TypeReference<Map<String, String>>() { });
                    for (Map.Entry<String, String> entry : devices.entrySet()) {
                        zDevices.addDevice(entry.getKey(), entry.getValue());
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            new Handler().postDelayed(this, 2000);
        }
    }

}
