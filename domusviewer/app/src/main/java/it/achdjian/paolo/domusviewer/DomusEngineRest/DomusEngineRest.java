package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.os.Handler;
import android.util.Log;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

import it.achdjian.paolo.domusviewer.Constants;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public abstract class DomusEngineRest implements Runnable {
    private static final String TAG = DomusEngineRest.class.getName();
    protected final SharedPreferences sharedPreferences;
    protected final ConnectionStatus connected;
    protected OkHttpClient client;
    public static final okhttp3.MediaType JSON = okhttp3.MediaType.parse("application/json; charset=utf-8");

    public DomusEngineRest(SharedPreferences sharedPreferences, ConnectionStatus connected) {
        this.sharedPreferences = sharedPreferences;
        this.connected = connected;
        init();
    }

    public DomusEngineRest(DomusEngineRest other) {
        this.sharedPreferences = other.sharedPreferences;
        this.connected = other.connected;
        init();
    }

    private void init() {
        client = new OkHttpClient.Builder().connectTimeout(10, TimeUnit.SECONDS).writeTimeout(10, TimeUnit.SECONDS).readTimeout(10, TimeUnit.SECONDS).build();
    }

    public String getAddress() {
        return sharedPreferences.getString(Constants.DOMUS_ENGINE_ADDRESS, "192.168.1.121");
    }

    public String get(String path) {
        String url = "http://" + getAddress() + path;

        Request request = new Request.Builder().url(url).get().header("Accept", "application/json").build();

        try {
            Response response = client.newCall(request).execute();
            if (response.code() == 200){
                return response.body().string();
            }
            if (response.code() == 204) {
                return "";
            }
        } catch (Exception ignored) {
            Log.e(TAG, "error", ignored);
        }
        Log.e(TAG, "ERROR");
        connected.setConnected(false);
        if (!WhoAreYou.isRunning()) {
            Handler handler = new Handler();
            handler.postDelayed(new WhoAreYou(this.sharedPreferences, this.connected), 1000);
        }

        return null;
    }

    public void post(String path)  {
        post(path,"");
    }


    public void post(String path, String body)  {
        String url = "http://" + getAddress() + path;
        RequestBody requestBody = RequestBody.create(JSON, body);
        Request request = new Request.Builder().url(url).post(requestBody).build();

        try {
            Response response = client.newCall(request).execute();

            if (response.code() == 200 || response.code() == 204) {
                return;
            }
        } catch (Exception e) {
            Log.e("DomusEngineRest", "Post", e);
        }
        Log.e(TAG, "ERROR");
        connected.setConnected(false);
        if (!WhoAreYou.isRunning()) {
            Handler handler = new Handler();
            handler.postDelayed(new WhoAreYou(this.sharedPreferences, this.connected), 1000);
        }
    }
}
