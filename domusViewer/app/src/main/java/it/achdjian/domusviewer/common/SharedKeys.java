package it.achdjian.domusviewer.common;

import android.annotation.SuppressLint;
import android.content.SharedPreferences;
import android.util.Log;

import it.achdjian.domusviewer.ScanningActivity.DomusEngineVersion;

/**
 * Created by Paolo Achdjian on 23/07/15.
 * Copyright Paolo Achdjian
 */
public class SharedKeys {
	public static final String PREFERENCE_NAME="preferences";

	private static final String TAG= SharedKeys.class.getName();

	private static final String DOMUS_ENGINE_ADDRESS = "domus_engine_address";
	private static final String DOMES_ENGINE_VERSION_MAJOR = "domes_engine_version_major";
	private static final String DOMES_ENGINE_VERSION_MEDIUM = "domes_engine_version_medium";
	private static final String DOMES_ENGINE_VERSION_MINOR = "domes_engine_version_minor";

	@SuppressLint("CommitPrefEdits")
	public static void  saveDomusEngineLocation(SharedPreferences sharedPreferences, String location, DomusEngineVersion version){
		SharedPreferences.Editor editor = sharedPreferences.edit();
		editor.putString(DOMUS_ENGINE_ADDRESS, location);
		editor.putInt(DOMES_ENGINE_VERSION_MAJOR, version.getMajorVersion());
		editor.putInt(DOMES_ENGINE_VERSION_MEDIUM, version.getMediumVersion());
		editor.putInt(DOMES_ENGINE_VERSION_MINOR, version.getMinorVersion());
		boolean commit = editor.commit();
		Log.d(TAG, "commit = " + commit);

	}

	public static String getDomusEngineLocation(SharedPreferences sharedPreferences){
		return sharedPreferences.getString(DOMUS_ENGINE_ADDRESS,new String());
	}
}