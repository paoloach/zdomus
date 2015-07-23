package it.achdjian.domusviewer.ScanningActivity;

import android.support.annotation.NonNull;
import android.util.Log;

/**
 * Created by Paolo Achdjian on 23/07/15.
 * Copyright Paolo Achdjian
 */
public class DomusEngineVersion {
	private final static String PREFIX="I am DomusEngine version";
	private static final String TAG = DomusEngineVersion.class.getName();
	private int majorVersion=0;
	private int mediumVersion=0;
	private int minorVersion=0;
	private boolean valid=false;

	public DomusEngineVersion(@NonNull String version){
		try {
		if (version.length() > PREFIX.length()){
			if (version.substring(0, PREFIX.length()).equals(PREFIX)){
				String strVersion = version.substring(PREFIX.length(), version.length());
				String[] split = strVersion.split("[.]");
				if (split.length == 3){
					majorVersion = Integer.parseInt(split[0].trim());
					mediumVersion = Integer.parseInt(split[1].trim());
					minorVersion = Integer.parseInt(split[2].trim());
					valid=true;
				}
			}
		}
		} catch (Exception e){
			Log.d(TAG, e.getMessage());
		}
	}

	public int getMajorVersion() {
		return majorVersion;
	}

	public int getMediumVersion() {
		return mediumVersion;
	}

	public int getMinorVersion() {
		return minorVersion;
	}

	public boolean isValid() {
		return valid;
	}

	@Override
	public String toString() {
		if (valid) {
			return "version {" +
					"minorVersion=" + minorVersion +
					", mediumVersion=" + mediumVersion +
					", majorVersion=" + majorVersion +
					'}';
		} else {
			return "invalid version";
		}
	}
}
