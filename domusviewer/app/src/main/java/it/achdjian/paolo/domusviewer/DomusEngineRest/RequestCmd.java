package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.support.annotation.NonNull;

import it.achdjian.paolo.domusviewer.DTO.CmdRequest;

/**
 * Created by Paolo Achdjian on 16/06/16.
 */
public class RequestCmd extends DomusEngineRest  {
    CmdRequest cmdRequest;

    public RequestCmd(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, CmdRequest cmdRequest) {
        super(sharedPreferences, connected);
        this.cmdRequest = cmdRequest;
    }

    @Override
    public void run() {
        post("/devices/"+cmdRequest.networkId+"/endpoint/"+cmdRequest.endpointId+"/cluster/in/"+cmdRequest.clusterId+"/command/"+cmdRequest.cmdId);
    }
}
