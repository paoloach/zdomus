package it.achdjian.domusviewer.domus_engine;

import android.util.Log;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.client.RestTemplate;

import it.achdjian.domusviewer.ScanningActivity.DomusEngineVersion;

/**
 * Created by Paolo Achdjian on 24/07/15.
 * Copyright Paolo Achdjian
 */
public class DomusEngine {
	private static final String TAG = DomusEngine.class.getName();

	public static DomusEngineVersion requestVersion(String target){
		RestTemplate restTemplate = new RestTemplate();
		String url = "http://" + target + ":8080/who_are_you";
		try {
			ResponseEntity<String> response = restTemplate.getForEntity(url, String.class);
			HttpStatus statusCode = response.getStatusCode();
			Log.d(TAG, "statusCode: " + statusCode.value());
			if (statusCode == HttpStatus.OK) {
				Log.d(TAG, "response: " + response.getBody());
				return new DomusEngineVersion(response.getBody());
			}
		} catch (Exception e) {
			String message = e.getMessage();
			if (message != null) {
				Log.d(TAG, message);
			}
		}
		return new DomusEngineVersion();
	}
}
