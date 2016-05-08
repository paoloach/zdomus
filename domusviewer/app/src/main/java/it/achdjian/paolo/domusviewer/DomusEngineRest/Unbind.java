package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.support.annotation.NonNull;

import it.achdjian.paolo.domusviewer.zigbee.BindRequestData;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public class Unbind extends DomusEngineRest  {
    @NonNull
    private final BindRequestData data;

    public interface Listener {
        void newDevice(JSonDevice zDevice);
    }


    public Unbind(@NonNull SharedPreferences sharedPreferences, @NonNull ConnectionStatus connected, @NonNull BindRequestData data) {
        super(sharedPreferences, connected);
        this.data = data;
    }

    @Override
    public void run() {
         post("/unbind/src/"+data.nwkSrc + "/endpoint/" + data.epSrc +"/cluster/" + data.cluster + "/dst/" + data.nwkDst + "/endpoint/" + data.epDst);
    }
}
