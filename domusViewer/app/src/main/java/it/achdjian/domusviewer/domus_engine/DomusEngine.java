package it.achdjian.domusviewer.domus_engine;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.support.annotation.NonNull;
import android.util.Log;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.client.RestTemplate;

import java.io.Closeable;
import java.io.IOException;
import java.util.Map;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

import it.achdjian.domusviewer.ScanningActivity.DomusEngineVersion;
import it.achdjian.domusviewer.ScanningActivity.ScanningResult;
import it.achdjian.domusviewer.common.SharedKeys;

/**
 * Created by Paolo Achdjian on 24/07/15.
 * Copyright Paolo Achdjian
 */
public class DomusEngine implements ScanningResult , Closeable {
	private static final String TAG = DomusEngine.class.getName();
	private static final int MAX_NUM_THREAD = 3;

	private Map<Integer,String> zAddresses;

	@NonNull
	private final Activity activity;

	private final ExecutorService executorService;

	public DomusEngine(@NonNull Activity activity) {
		this.activity = activity;
		executorService = Executors.newFixedThreadPool(MAX_NUM_THREAD);
	}

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

	@Override
	public void serverFound() {
		Log.d(TAG, "Unable to find DomusEngine Server");
		String domusEngineLocation = SharedKeys.getDomusEngineLocation(activity.getSharedPreferences(SharedKeys.PREFERENCE_NAME, Context.MODE_PRIVATE));
		Future<Map<Integer, String>> objectsFuture = executorService.submit(new GetAllZObjects(domusEngineLocation));
		try {
			zAddresses = objectsFuture.get();
		} catch (InterruptedException e) {
			e.printStackTrace();
			return;
		} catch (ExecutionException e) {
			e.printStackTrace();
			return;
		}

	}

	@Override
	public void serverNotFound() {

	}

	@Override
	public void close() throws IOException {
		executorService.shutdown();
		try {
			executorService.awaitTermination(5, TimeUnit.SECONDS);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
