package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.support.annotation.NonNull;

import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class RequestIdentify extends DomusEngineRest  {
    private final int nwkAddress;
    private final int endpoint;

    public RequestIdentify(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, int nwkAddress, int endpoint) {
        super(sharedPreferences, connected);
        this.nwkAddress = nwkAddress;
        this.endpoint = endpoint;
    }

    @Override
    public void run() {
         post("/devices/"+nwkAddress+"/endpoint/"+endpoint+"/cluster/in/3/command/0");
    }
}
