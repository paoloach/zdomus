package it.achdjian.paolo.domusviewer.DomusEngineRest;

import android.content.SharedPreferences;
import android.os.Handler;
import android.util.Log;

import org.springframework.http.HttpEntity;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.SimpleClientHttpRequestFactory;
import org.springframework.web.client.RestTemplate;

import it.achdjian.paolo.domusviewer.Constants;

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
public abstract class DomusEngineRest implements Runnable {
    private static final String TAG = DomusEngineRest.class.getName();
    protected final SharedPreferences sharedPreferences;
    protected final ConnectionStatus connected;

    public DomusEngineRest(SharedPreferences sharedPreferences, ConnectionStatus connected) {
        this.sharedPreferences = sharedPreferences;
        this.connected = connected;
    }

    public DomusEngineRest(DomusEngineRest other) {
        this.sharedPreferences = other.sharedPreferences;
        this.connected = other.connected;
    }

    public String getAddress() {
        return sharedPreferences.getString(Constants.DOMUS_ENGINE_ADDRESS, "192.168.1.121");
    }

    public String get(String path){
        SimpleClientHttpRequestFactory factory = new SimpleClientHttpRequestFactory();
        factory.setReadTimeout(20000);
        factory.setConnectTimeout(20000);
        RestTemplate restTemplate = new RestTemplate(factory);
        String url = "http://" + getAddress() + path;
        Handler handler = new Handler();

        try {
            Log.d(TAG,"request: " + url);
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.APPLICATION_JSON);
            HttpEntity<String> entity = new HttpEntity<>(headers);
            ResponseEntity<String> response = restTemplate.exchange(url, HttpMethod.GET,entity,String.class);
            Log.d(TAG,"response: " + response.getStatusCode().getReasonPhrase());
            if (response.getStatusCode() == HttpStatus.OK) {
                String body = response.getBody();
                if (body != null) {
                    return body;
                }

            }
        } catch (Exception ignored) {
        }
        Log.e(TAG, "ERROR");
        connected.setConnected(false);
        handler.postDelayed(new WhoAreYou(this.sharedPreferences, this.connected), 1000);
        return null;
    }

}
