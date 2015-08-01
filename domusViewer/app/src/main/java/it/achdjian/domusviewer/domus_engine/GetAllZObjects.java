package it.achdjian.domusviewer.domus_engine;

import android.support.annotation.NonNull;
import android.util.Log;

import com.fasterxml.jackson.core.JsonGenerationException;
import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.http.converter.json.MappingJackson2HttpMessageConverter;
import org.springframework.web.client.RestTemplate;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Callable;

/**
 * Created by Paolo Achdjian on 30/07/15.
 * Copyright Paolo Achdjian
 */
public class GetAllZObjects implements Callable<Map<Integer,String>> {
	private static final String TAG = GetAllZObjects.class.getName();
	private final String address;

	public GetAllZObjects(String address) {
		this.address = address;
	}

	@Override
	@NonNull
	public Map<Integer, String> call() throws Exception {
		Map<Integer, String> result = null;
		RestTemplate restTemplate = new RestTemplate();
		restTemplate.getInterceptors().add(new DomusEngineInterceptor() );
		restTemplate.getMessageConverters().add( new MappingJackson2HttpMessageConverter());
		String url = "http://" + address + ":8080/devices";
		try {
			ResponseEntity<String> response = restTemplate.getForEntity(url, String.class);
			HttpStatus statusCode = response.getStatusCode();
			Log.d(TAG, "statusCode: " + statusCode.value());
			if (statusCode == HttpStatus.OK) {
				String body = response.getBody();
				ObjectMapper objectMapper = new ObjectMapper();
				result  = objectMapper.readValue(body, new TypeReference<Map<Integer, String>>() {});
				Log.d(TAG,"JSON: " + body);
				Log.d(TAG, "map: " + Arrays.toString(result.entrySet().toArray()));
			}
		}catch (JsonGenerationException | JsonMappingException e)	{
			e.printStackTrace();
		} catch (Exception e) {
			String message = e.getMessage();
			if (message != null) {
				Log.d(TAG, message);
			}
		}
		if (result==null){
			return new HashMap<>();
		} else {
			return result;
		}
	}

}
