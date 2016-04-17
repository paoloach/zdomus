package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.os.Handler;
import android.util.Log;

/**
 * Created by Paolo Achdjian on 14/04/16.
 */
public class WhoAreYou extends DomusEngineRest {
    private static final String TAG = WhoAreYou.class.getName();
    private static final String EXPECTED_NAME = "I am DomusEngine";

    public WhoAreYou(SharedPreferences sharedPreferences, ConnectionStatus connected) {
        super(sharedPreferences, connected);
    }

    @Override
    public void run() {
        String body = get("/who_are_you");
        if (body != null) {
            if (body.substring(0, EXPECTED_NAME.length()).equals(EXPECTED_NAME)) {
                connected.setConnected(true);
                Log.d(TAG, "Server found");
                return;
            }
        }
        connected.setConnected(false);
        new Handler().postDelayed(this, 1000);
    }
}
